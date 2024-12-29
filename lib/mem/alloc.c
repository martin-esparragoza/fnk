#include "include/mem/alloc.h"
#include "alloc.h"
#include <stddef.h>
#include <stdint.h>

// Init args set in entry
void* mem_alloc_heap_start = NULL;

static void* heap_end; // Yes, there is no heap end however this is where the unlimited section begins
static struct mem_alloc_heap_entry* heap_head;

const char* mem_alloc_errcstr[] = {
    [MEM_ALLOC_ERRC_OK] = "Ok",
};

int mem_alloc_init() {
    heap_head = NULL;
    
    heap_end = mem_alloc_heap_start;
    
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
        if (entry->size >= size && entry->flags & MEM_ALLOC_HEAP_ENTRY_FLAG_FREE)
            break;

        entry = entry->next;
    }
    
    if (entry == NULL) { // No section found; allocate in unlimited land!
        struct mem_alloc_heap_entry* new_entry = heap_end;
        heap_end += sizeof(struct mem_alloc_heap_entry) + size;
        new_entry->size = size;
        new_entry->flags = entry->flags & !MEM_ALLOC_HEAP_ENTRY_FLAG_FREE;
        new_entry->next = heap_head; // P sure if heap_head is null this still works
        heap_head = new_entry;
        *b = (void*) (heap_head + sizeof(struct mem_alloc_heap_entry));
    } else { // Otherwise we can attempt to split it into two
        // Going to create and insert the new segment first because many of the values in the new segment are inherited or require old segment values
        if ((size + sizeof(struct mem_alloc_heap_entry) /* clip it TODO: bc */) < entry->size) {
            struct mem_alloc_heap_entry* new_entry = (void*) (((uintptr_t) entry) + sizeof(struct mem_alloc_heap_entry) + size);
            // First 2 parts just gets the location of the end then we add the size to get the end

            new_entry->size = entry->size - size - sizeof(struct mem_alloc_heap_entry);
            new_entry->flags = entry->flags; // FREE should already be on

            // Insertion into ll
            new_entry->next = heap_head;
            heap_head = new_entry;

            entry->size = size; // Only set the size to reduced if we meet the threshold; otherwise no clip it to the largest possible
        }
        
        // Finally making the old entry occupied
        entry->flags &= !MEM_ALLOC_HEAP_ENTRY_FLAG_FREE; // Mark it as used
        *b = (void*) (((uintptr_t) entry) + sizeof(struct mem_alloc_heap_entry)); // Return val
    }
    
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