/**
 * @file memops.h
 * @brief Memory operations
 * Functions
 */

#ifndef BOOT_INCLUDE_MEMOPS_H_
#define BOOT_INCLUDE_MEMOPS_H_

#include "types.h"
#include "attr.h"

void fnk_memops_bswap(void* data, size_t size);

uint16_t fnk_memops_bswap16(uint16_t data);

uint32_t fnk_memops_bswap32(uint32_t data);

uint64_t fnk_memops_bswap64(uint64_t data);

/**
 * @brief Aligns along power of 2 boundry
 *
 * @return Unexpeceted behavior if toalign is not a power of 2 otherwise the right value
 */
uintptr_t fnk_memops_alignp2(uintptr_t value, int toalign);

void fnk_memops_memcpy(void* dest, const void* src, size_t length);

void fnk_memops_memset(void* dest, uint8_t val, size_t length);

void fnk_memops_memcmp(const void* ptr0, const void* ptr1, size_t length);

#endif