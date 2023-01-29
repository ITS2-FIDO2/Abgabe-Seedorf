#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "shell.h"
//#include "shell_commands.h"
#include "od.h"
#include "random.h"

#include "crypto/modes/cbc.h"
#include "crypto/ciphers.h"
#include "crypto/aes.h"

static cipher_t cipher;

uint8_t *decrypt(uint8_t *buffer, uint8_t iv[16], size_t size)
{
    if (!buffer || size <= 0 || size % AES_BLOCK_SIZE)
    {
        return NULL; // Eingabevalidierung
    }

    // Alloziere Speicher für die Ausgabe
    uint8_t *output = malloc(size);

    // Verschlüsseln
    int err = cipher_decrypt_cbc(&cipher, iv, buffer, size, output);

    if (err < 0)
    {
        printf("Failed to decrypt data: %d\n", err);
        exit(err);
    }

    return output;
}

uint8_t *encrypt(void *buffer, size_t size, uint8_t iv[16], size_t *size_out)
{
    if (!buffer || !size_out)
    {
        return NULL; // Eingabevalidierung
    }

    // Berechne die Menge an Blöcken
    size_t amount_blocks = size / AES_BLOCK_SIZE;

    if (size % AES_BLOCK_SIZE)
    {
        ++amount_blocks;
    }

    // Berechnung der Eingabe und Ausgabegrößen
    *size_out = sizeof(uint8_t) * (amount_blocks * AES_BLOCK_SIZE);

    // Eingabe padden
    uint8_t *input = calloc((amount_blocks * AES_BLOCK_SIZE), sizeof(uint8_t)); // calloc initialisiert den Speicher zusätzlich mit Nullen
    memcpy((void *)input, buffer, size);

    // Alloziere Speicher für die Ausgabe
    uint8_t *output = malloc(*size_out);

    // IV generieren
    random_bytes(iv, 16); // In Produktionsumgebungen eine Kryptographisch sichere Random Funktion verwenden!!!

    // Verschlüsseln
    int err = cipher_encrypt_cbc(&cipher, iv, input, *size_out, output);

    if (err < 0)
    {
        printf("Failed to encrypt data: %d\n", err);
        exit(err);
    }

    free(input);
    return output;
}

uint8_t *encrypt_string(char *string, uint8_t iv[16], size_t *size_out)
{
    return encrypt((void *)string, strlen(string) + 1, iv, size_out);
}

int encrypt_command_handler(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Syntax: %s <message>\n", argv[0]);
        return 1;
    }

    size_t size;
    uint8_t iv[16];

    uint8_t *encrypted = encrypt_string(argv[1], iv, &size);
    uint8_t *decrypted = decrypt(encrypted, iv, size);

    printf("IV: ");
    od_hex_dump_ext(iv, 16, 0, 0);
    printf("\n");

    od_hex_dump_ext(argv[1], strlen(argv[1]) + 1, AES_BLOCK_SIZE, 0);
    printf("\n");
    od_hex_dump_ext(encrypted, size, AES_BLOCK_SIZE, 0);
    printf("\n");
    od_hex_dump_ext(decrypted, size, AES_BLOCK_SIZE, 0);

    free(encrypted);
    free(decrypted);

    return 0;
}

int main(void)
{
    uint8_t key[] = {
        0x64, 0x52, 0x67, 0x55,
        0x6B, 0x58, 0x70, 0x32,
        0x73, 0x35, 0x75, 0x38,
        0x78, 0x2F, 0x41, 0x3F};

    int err = cipher_init(&cipher, CIPHER_AES, key, AES_KEY_SIZE_128);

    if (err != CIPHER_INIT_SUCCESS)
    {
        printf("Cipher Init failed: %d\n", err);
        exit(err);
    }

    shell_command_t commands[] = {
        {"encrypt", "encrypt a message", encrypt_command_handler},
        {NULL, NULL, NULL}};

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
