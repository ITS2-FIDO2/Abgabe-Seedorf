#include <stdio.h>
#include "od.h"
#include "crypto/aes.h"
#include "aes-ecb.h"

void executeAesEcb(int numberOfRounds, int keySize, size_t messageLength) {
    for(int round = 1; round <= numberOfRounds; round++){
        uint8_t* input = malloc(messageLength);
        random_bytes(input, messageLength);
        uint8_t* decryptBuffer = malloc(messageLength);
        cipher_context_t cipher;
        int requiredBlocks = messageLength / AES_BLOCK_SIZE;
        if(messageLength % AES_BLOCK_SIZE) {
            requiredBlocks++;
        }
        uint8_t* output = calloc(requiredBlocks, AES_BLOCK_SIZE);
        uint8_t* key = malloc(keySize);
        random_bytes(key, keySize);
        int err = aes_init(&cipher, key, keySize);
        if(err != CIPHER_INIT_SUCCESS){
            printf("Cipher init failed: %d", err);
            exit(0);
        }
        //printf("Key:\n");
        //od_hex_dump(key, keySize, 0);
        uint32_t _benchmark_time_encryption = xtimer_now_usec();
        aes_encrypt(&cipher, input, output);
        _benchmark_time_encryption = (xtimer_now_usec() - _benchmark_time_encryption);
        /*printf("Plaintext: \t");
        od_hex_dump(input, AES_BLOCK_SIZE, 0);
        printf("Ciphertext: \t");
        od_hex_dump(output, AES_BLOCK_SIZE, 0);*/
        uint32_t _benchmark_time_decryption = xtimer_now_usec();
        aes_decrypt(&cipher, output, decryptBuffer);
        _benchmark_time_decryption = (xtimer_now_usec() - _benchmark_time_decryption);
        /*printf("Decrypted text: \t");
        od_hex_dump(decryptBuffer, AES_BLOCK_SIZE, 0);*/
        uint32_t benchmarkResults[2];
        benchmarkResults[0] = _benchmark_time_encryption;
        benchmarkResults[1] = _benchmark_time_decryption;
        printf(";%d;%lu;%lu\n", round, benchmarkResults[0], benchmarkResults[1]);
        free(input);
        free(output);
        free(decryptBuffer);
        free(key);
    }
}
