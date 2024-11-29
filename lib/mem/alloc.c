#include "include/mem/alloc.h"
#include "alloc.h"
#include <stddef.h>
#include <stdint.h>

// Init args set in entry
void* mem_alloc_heap_start = NULL;

static struct mem_alloc_heap_entry* heap_head;

const char* mem_alloc_errcstr[] = {
    [MEM_ALLOC_ERRC_OK] = "Ok",
    [MEM_ALLOC_ERRC_HEAP_INIT_FAIL] = "Could not init heap",
    [MEM_ALLOC_ERRC_HEAP_NO_SPACE] = "No space for attempted allocation"
};

int mem_alloc_init() {
    // Cast over thats pretty much all we need to do
    heap_head = (struct mem_alloc_heap_entry*) mem_alloc_heap_start;

    heap_head->size = 0;
    heap_head->flags = MEM_ALLOC_HEAP_ENTRY_FLAG_FREE | MEM_ALLOC_HEAP_ENTRY_FLAG_UNLIMITED;
    heap_head->next = NULL;
    
    return MEM_ALLOC_ERRC_OK;
}

const char* mem_alloc_errctostr(int errc) {
    if (errc < sizeof(mem_alloc_errcstr) / sizeof(mem_alloc_errcstr[0]))
        return mem_alloc_errcstr[errc];

    return NULL;
}

int mem_alloc_malloc(void** b, size_t size) {
    // First find a section of memory that can be allocated
    struct mem_alloc_heap_entry* entry = heap_head;

    while (entry != NULL) {
        // Check if enough room for allocation
        if (
            (entry->size >= size ||
            entry->flags & MEM_ALLOC_HEAP_ENTRY_FLAG_UNLIMITED) &&
            entry->flags & MEM_ALLOC_HEAP_ENTRY_FLAG_FREE)
            break;

        entry = entry->next;
    }
    
    if (entry == NULL)
        return MEM_ALLOC_ERRC_HEAP_NO_SPACE;

    // Now create new entry (allocate it in heap space)
    if (entry->next == NULL) {
        struct mem_alloc_heap_entry* prevnext = entry->next;
        entry->next = (void*) &(entry->data[size]);
        entry->next->flags = entry->flags;
        entry->next->size = entry->size - size;
        entry->next->next = prevnext;
    }
    
    // Allocate section after because we are done copying over values
    entry->size = size;
    entry->flags ^= MEM_ALLOC_HEAP_ENTRY_FLAG_FREE;
    entry->flags &= !MEM_ALLOC_HEAP_ENTRY_FLAG_UNLIMITED; // Turn off unlimited

    *b = entry->data;

    return MEM_ALLOC_ERRC_OK;
}

int mem_alloc_calloc(void** b, size_t num, size_t size);

int mem_alloc_realloc(void* ptr, size_t size);

int mem_alloc_free(void* ptr);

int mem_alloc_fini() {
    mem_alloc_heap_start = NULL;
    heap_head = NULL;

    return MEM_ALLOC_ERRC_OK;
}