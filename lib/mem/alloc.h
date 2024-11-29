// TODO: Docs

#ifndef LIB_MEM_ALLOC_H_
#define LIB_MEM_ALLOC_H_

#include "attr.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define MEM_ALLOC_HEAP_ENTRY_FLAG_FREE 0b00000001 ///< Portion of memory is free
#define MEM_ALLOC_HEAP_ENTRY_FLAG_UNLIMITED 0b00000010 ///< Portion of memory has an unlimited size (discard size qualifier)

typedef struct INCLUDE_COMP_ATTR_PACKED mem_alloc_heap_entry {
    uintptr_t size;
    uint8_t flags;
    struct mem_alloc_heap_entry* next;
    uint8_t data[]; ///< This is the returned ptr value
} mem_alloc_heap_entry;

#endif