/**
 * @file ops.h
 * @brief Easy operations that you might need
 */

#ifndef LIB_UTIL_OPS_H_
#define LIB_UTIL_OPS_H_

#include "types.h"
#include "attr.h"

void util_ops_bswap(void* data, size_t size);

uint16_t util_ops_bswap16(uint16_t data);

uint32_t util_ops_bswap32(uint32_t data);

uint64_t util_ops_bswap64(uint64_t data);

bool util_ops_ispowertwo(unsigned x);

int util_ops_min(int a, int b);

int util_ops_max(int a, int b);

uintptr_t align(uintptr_t value, int toalign);

void memcpy(void* dest, void* src, size_t length);

void memset(void* dest, char c, size_t length);


#endif