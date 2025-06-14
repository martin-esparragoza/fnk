/**
 * @file mem.h
 * @brief Memory operations
 */

#ifndef LIB_UTIL_MEM_H_
#define LIB_UTIL_MEM_H_

#include "types.h"

void util_mem_bswap(void* data, size_t size);

uint16_t util_mem_bswap16(uint16_t data);

uint32_t util_mem_bswap32(uint32_t data);

uint64_t util_mem_bswap64(uint64_t data);

uintptr_t util_mem_align(uintptr_t value, int toalign);

void util_mem_memcpy(void* dest, void* src, size_t length);

void util_mem_memset(void* dest, uint8_t val, size_t length);

void util_mem_memcmp(void* ptr0, void* ptr1, size_t length);

#endif