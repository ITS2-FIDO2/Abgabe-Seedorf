#ifndef AES_CBC_H
#define AES_CBC_H

#include "random.h"
#include <stdio.h>
#include "xtimer.h"
#include "crypto/modes/cbc.h"

void executeAesCbc(int numberOfRounds, int keySize, size_t messageLength);

#endif
