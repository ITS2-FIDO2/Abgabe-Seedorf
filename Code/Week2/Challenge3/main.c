#include <stdio.h>

#include "crypto/ciphers.h"
#include "crypto/aes.h"
#include "crypto/modes/ctr.h"

#include "od.h"

#include "random.h"

static const uint8_t key[] = {
        0x64, 0x52, 0x67, 0x55,
        0x6B, 0x58, 0x70, 0x32,
        0x73, 0x35, 0x75, 0x38,
        0x78, 0x2F, 0x41, 0x3F};

int main(void)
{
    /*
     * The message contains all hexadecimal digits concatenated 6 times.
     * This makes it easy to see in the ciphertext that the same plaintext block encrypted with CBC gives different results.
     */
    const char* message = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";

    /* ======== Cipher initialization ======== */

    cipher_t cipher;
    int err;

    if ((err = cipher_init(&cipher, CIPHER_AES, key, AES_KEY_SIZE_128)) != CIPHER_INIT_SUCCESS) {
        printf("Failed to init cipher: %d\n", err);
        return err;
    }

    /* ======== Calculating length ======== */

    int data_len = strlen(message) + 1;
    int n_required_blocks = data_len / AES_BLOCK_SIZE;

    if (data_len % AES_BLOCK_SIZE) {
        n_required_blocks++;
    }

    size_t total_len = n_required_blocks * AES_BLOCK_SIZE;

    /* ======== Create buffers ======== */

    uint8_t* input = calloc(n_required_blocks, AES_BLOCK_SIZE);
    uint8_t* output = calloc(n_required_blocks, AES_BLOCK_SIZE);
    uint8_t* decrypted = calloc(n_required_blocks, AES_BLOCK_SIZE);

    memcpy(input, message, data_len);

    /* ======== Create counter_block and fill with random Nonce and counter starting at 0======== */

    uint8_t counter_block[16] = {0};

    uint8_t nonce[8] = {0};
    random_bytes(nonce, 8); // IMPORTANT: In productive environment, use a cryptographically secure RNG!
    uint8_t counter[8] = {1}; // IMPORTANT: In productive environment, use a cryptographically secure RNG!

    // Concat
    memcpy(counter_block, nonce, 8);
    memcpy(counter_block + 8, counter, 8);

    /* ======== Encryption and Decryption ======== */

    if ((err = cipher_encrypt_ctr(&cipher, counter_block, 8, input, total_len, output)) < 0) {
        printf("Failed to encrypt data: %d\n", err);
        return err;
    }

        if ((err = cipher_decrypt_ctr(&cipher, counter_block, 8, output, total_len, decrypted)) < 0) {
        printf("Failed to decrypt data: %d\n", err);
        return err;
    }

    /* ======== Output ======== */

    printf("IV: ");
    od_hex_dump(counter_block, 16, 0);
    printf("\n\n");

    printf("Plaintext:\n");
    od_hex_dump(input, total_len, AES_BLOCK_SIZE);
    printf("\n\n");

    printf("Ciphertext:\n");
    od_hex_dump(output, total_len, AES_BLOCK_SIZE);
    printf("\n\n");

    printf("Decrypted Ciphertext:\n");
    od_hex_dump(input, total_len, AES_BLOCK_SIZE);
    printf("\n\n");

    /* ======== Cleanup ======== */

    free(input);
    free(output);
    free(decrypted);

    return 0;
}