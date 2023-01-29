#include "algorithms/aes-ecb.h"
#include "algorithms/aes-cbc.h"
#include "algorithms/aes-ctr.h"
#include <stdio.h>
#include <stdint.h>
#include "time.h"
#include "string.h"


#define ROUNDS 1000
#define MESSAGE_LENGTH 131072 // in BYTES
#define KEY_SIZE 24 // in BYTES

int main(void)
{
    printf("Starting Benchmark ...\nNUMBER OF ROUNDS: %d\nWORDLENGTH: %d BYTES\nKEY SIZE: %d BYTES\n", ROUNDS, MESSAGE_LENGTH, KEY_SIZE);
    
    if (KEY_SIZE <= 24) {
        printf("Mode: ELECTRONIC CODEBOOK\n");
        executeAesEcb(ROUNDS, KEY_SIZE, MESSAGE_LENGTH);
    }
    
    printf("\nMode: CIPHER BLOCKER CHAINING\n");
    executeAesCbc(ROUNDS, KEY_SIZE, MESSAGE_LENGTH);

    printf("\nMode: COUNTER\n");
    executeAesCtr(ROUNDS, KEY_SIZE, MESSAGE_LENGTH);
    
    printf("\nBenchmark done!\n");
    return 0;
}
