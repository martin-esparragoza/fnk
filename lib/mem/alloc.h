/**
 * @file alloc.h
 * @brief Structure definitions for alloc.c
 */

#ifndef LIB_MEM_ALLOC_H_
#define LIB_MEM_ALLOC_H_

#include "attr.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define MEM_ALLOC_HEAP_ENTRY_FLAG_FREE      0b00000001 ///< Portion of memory is free

/**
 * @brief Serves as a descriptor
 * Actual data is always above it so addresses can be fetched by + or - sizeof this structure
 */
typedef struct INCLUDE_COMP_ATTR_PACKED mem_alloc_heap_entry {
    uintptr_t size; ///< Size in bytes (this should probably be changed... I can see this as annoying legacy)
    uint8_t flags; ///< Look at the MEM_ALLOC_HEAP_ENTRY_FLAG_*
    struct mem_alloc_heap_entry* next; ///< Next entry
} mem_alloc_heap_entry;

#endif