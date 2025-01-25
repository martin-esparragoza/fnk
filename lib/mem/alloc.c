#include "include/mem/alloc.h"
#include "alloc.h"
#include <stddef.h>
#include <stdint.h>

// Init args set in entry
void* mem_alloc_heap_start = NULL;

static void* heap_end; // Yes, there is no heap end however this is where the unlimited section begins
static struct mem_alloc_heap_entry* heap_head;


void mem_alloc_init() {
    heap_head = NULL;
    
    heap_end = mem_alloc_heap_start;
}

// TODO: SP head check
void* mem_alloc_malloc(size_t size) {
    // First find a section of memory that can be allocated
    struct mem_alloc_heap_entry* entry;
    
    // Find an entry in the list that could house it
    for (
        entry = heap_head;
        entry != NULL && entry->size < size;
        entry = entry->next
    );
    
    // TODO: Alignment shenanigans
    if (entry == NULL) { // No section found; allocate in unlimited land!
        // Increase the size of the heap and add our new element. This descriptor data will be invisible
        heap_end += sizeof(struct mem_alloc_heap_entry) + size;
        struct mem_alloc_heap_entry* new_entry = heap_end;
        new_entry->size = size;

        // DON'T add it to the linked list. We will add it later when we FREE it
        return (void*) (((uintptr_t) new_entry) - sizeof(struct mem_alloc_heap_entry));
    } else { // Otherwise we can attempt to split it into two
        
        // To do this first repurpose the previous heap entry
        uintptr_t new_entry_size = entry->size - size; // We have to add a free segment
        entry->size = size;
        // Don't alter next. It will be altered to be inserted to the front of the LL later

        // Regardless we need to find the prev entry so we can chop this out of the LL
        struct mem_alloc_heap_entry* prev = NULL;
        for (
            struct mem_alloc_heap_entry* e = heap_head;
            e->next != NULL;
            prev = e, e = e->next
        );
        
        if (new_entry_size > sizeof(struct mem_alloc_heap_entry)) {
            // Create new entry
            struct mem_alloc_heap_entry* new_entry = (void*) (((uintptr_t) entry) + sizeof(mem_alloc_heap_entry) + size);
            if (prev != NULL) // Chop it out of ll
                prev->next = new_entry;
            else
                heap_head = new_entry;
            new_entry->next = entry->next; // Assumes the perfect thing that entry->next must be NULL if at end
            new_entry->size = new_entry_size - sizeof(mem_alloc_heap_entry);

        // This thing is to chop out of ll
        } else {
            // We don't have enough space. Add it to the return entry
            entry->size += new_entry_size;

            if (prev != NULL)
                prev->next = entry->next;
            else // If prev is NULL that means it was the head
                heap_head = entry->next;
        }
        
        return (void*) (((uintptr_t) entry) - sizeof(struct mem_alloc_heap_entry));
    }
}

void* mem_alloc_calloc(uint64_t value, size_t size);

void* mem_alloc_realloc(void* b, size_t size);

void mem_alloc_free(void* ptr) {
    struct mem_alloc_heap_entry* entry = ((struct mem_alloc_heap_entry*) ptr) + 1;
    
    entry->next = heap_head;
    heap_head = entry;
}

void mem_alloc_fini() {
    mem_alloc_heap_start = NULL;
    heap_head = NULL;
}