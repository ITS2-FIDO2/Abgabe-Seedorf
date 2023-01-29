#ifndef AES_ECB_H
#define AES_ECB_H

#include "random.h"
#include <stdio.h>
#include "xtimer.h"

void executeAesEcb(int numberOfRounds, int keySize, size_t messageLength);

#endif
