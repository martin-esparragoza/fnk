/**
 * @file memops.h
 * @brief Memory operations
 */

#ifndef INCLUDE_RTFNK_MEMOPS_H_
#define INCLUDE_RTFNK_MEMOPS_H_

#include "types.h"
#include "attr.h"

void COMP_ATTR__WEAK__ rtfnk_memops_bswap(void* data, size_t size);

uint16_t COMP_ATTR__WEAK__ rtfnk_memops_bswap16(uint16_t data);

uint32_t COMP_ATTR__WEAK__ rtfnk_memops_bswap32(uint32_t data);

uint64_t COMP_ATTR__WEAK__ rtfnk_memops_bswap64(uint64_t data);

uintptr_t COMP_ATTR__WEAK__ rtfnk_memops_align(uintptr_t value, int toalign);

void COMP_ATTR__WEAK__ rtfnk_memops_memcpy(void* dest, void* src, size_t length);

void COMP_ATTR__WEAK__ rtfnk_memops_memset(void* dest, uint8_t val, size_t length);

void COMP_ATTR__WEAK__ rtfnk_memops_memcmp(void* ptr0, void* ptr1, size_t length);

#endif