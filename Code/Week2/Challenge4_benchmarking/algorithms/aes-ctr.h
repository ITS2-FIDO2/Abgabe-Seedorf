#ifndef AES_CTR_H
#define AES_CTR_H

#include "random.h"
#include <stdio.h>
#include "xtimer.h"
#include "crypto/modes/ctr.h"

void executeAesCtr(int numberOfRounds, int keySize, size_t messageLength);

#endif
