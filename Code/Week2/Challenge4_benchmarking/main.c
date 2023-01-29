#include "algorithms/aes-ecb.h"
#include "algorithms/aes-cbc.h"
#include <stdio.h>
#include <stdint.h>
#include "time.h"
#include "string.h"


#define ROUNDS 1000
#define MESSAGE_LENGTH 2048 // in BYTES
#define KEY_SIZE 24 // in BYTES
#define ECB_MODE 0 // 0=OFF, 1=ON

int main(void)
{
    printf("Starting Benchmark ...\nNUMBER OF ROUNDS: %d\nWORDLENGTH: %d BYTES\n", ROUNDS, MESSAGE_LENGTH);
    if(ECB_MODE){
        printf("Mode: ELECTRONIC CODEBOOK\n");
        executeAesEcb(ROUNDS, KEY_SIZE, MESSAGE_LENGTH);
    } else {
        printf("Mode: CIPHER BLOCKER CHAINING\n");
        executeAesCbc(ROUNDS, KEY_SIZE, MESSAGE_LENGTH);
    }
    printf("Benchmark done!\n");
    return 0;
}
