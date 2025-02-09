/**
 * @file ops.h
 * @brief Easy operations that you might need
 */

#ifndef LIB_UTIL_OPS_H_
#define LIB_UTIL_OPS_H_

#include "types.h"

void util_ops_bswap(uint8_t* data, size_t size);

inline bool util_ops_ispowertwo(unsigned x) {
    return x && !(x & (x - 1)); // && x to make sure x != 0
}

int util_ops_min(int a, int b);

int util_ops_max(int a, int b);

#endif