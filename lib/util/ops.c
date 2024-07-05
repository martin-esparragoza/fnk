#include "ops.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void util_ops_bswap(uint8_t* data, size_t size) {
    for (size_t i = 0; i < size / 2; i++) {
        data[i] ^= data[size - i - 1];
        data[size - i - 1] ^= data[i];
        data[i] ^= data[size - i - 1];
    }
}

extern inline bool util_ops_ispowertwo(unsigned x);