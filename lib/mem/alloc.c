#include "include/mem/alloc.h"
#include "include/rtfnk/memops.h"
#include "lib/util/ops.c"
#include "alloc.h"
#include "types.h"
#include "config.h"

// Init args set in entry
void* mem_alloc_heap_start = NULL;

static void* heap_end; // Yes, there is no heap end however this is where the unlimited section begins SO TECHNICALLY ITS A HEAP START????? HUHHHHH
static struct mem_alloc_heap_entry* heap_head;
static unsigned char _coalescing_max = 0;
static unsigned char coalescing_prio = 0;

static void coalesce() {
    // O(n)
    struct mem_alloc_heap_entry* next = NULL, * entry = heap_head;
    while (entry->next != NULL) {
        // Check if on the same bounds
        if (((uintptr_t) entry) - entry->size - sizeof(struct mem_alloc_heap_entry) == (uintptr_t) next) {
            // Coalesce them
            entry->next = next->next;
            entry->size += next->size + sizeof(struct mem_alloc_heap_entry);
            next = next->next; // For the update loop
            
            continue; // Redo that loop
        }

        entry = entry->next;
        next = entry->next;
    }
}

// Effectively lazy coalescing
static void inc_coalesce();
static inline void inc_coalesce() {
    if (++coalescing_prio >= _coalescing_max) {
        coalesce();
        coalescing_prio = 0;
    }
}


void mem_alloc_init(unsigned char coalescing_max) {
    heap_head = NULL;
    
    // If you do not pass this as an aligned value you are being STUPID
    heap_end = mem_alloc_heap_start;
    
    _coalescing_max = coalescing_max;
}

void* mem_alloc_malloc(size_t size) {
    if (!size)
        return NULL;
    
    // Ok it is weird to do this but it geuinely just works...
    size = fnk_memops_alignp2(size, sizeof(uintptr_t));
    size += fnk_memops_alignp2(sizeof(struct mem_alloc_heap_entry), sizeof(uintptr_t)) - sizeof(struct mem_alloc_heap_entry);
    
    // First find a section of memory that can be allocated
    struct mem_alloc_heap_entry* entry;
    
    // Find an entry in the list that could house it
    for (
        entry = heap_head;
        entry != NULL && entry->size < size;
        entry = entry->next
    );
    
    if (entry == NULL) { // No section found; allocate in unlimited land!
        // Increase the size of the heap and add our new element. This descriptor data will be invisible
        struct mem_alloc_heap_entry* new_entry = heap_end;
        (new_entry++)->size = size; // We're done with new entry so now we just want the return buffer
        heap_end += size + sizeof(struct mem_alloc_heap_entry);

        // DON'T add it to the linked list. We will add it later when we FREE it
        return (void*) new_entry;
    } else { // Otherwise we can attempt to split it into two
        // Find the prev entry so we can chop this out of the LL
        struct mem_alloc_heap_entry* prev = NULL;
        // Previous if already checked if heap_head == NULL
        for (
            struct mem_alloc_heap_entry* e = heap_head;
            e->next != NULL && e != entry;
            prev = e, e = e->next
        );

        // Clip!
        if (prev != NULL)
            prev->next = entry->next;
        else // If prev is NULL that means it was the head
            heap_head = entry->next;
        
        if (entry->size - size > sizeof(struct mem_alloc_heap_entry)) { // Splitable. Otherwise stays as entry->size
            // Create new entry
            struct mem_alloc_heap_entry* new_entry = (void*) (((uintptr_t) (entry + 1)) + size);
            new_entry->size = entry->size - size - sizeof(struct mem_alloc_heap_entry);
            
            // This counts as sorted insertion because prev and next should be relative
            if (prev != NULL)
                prev->next = new_entry;
            else // At the head
                heap_head = new_entry;
            new_entry->next = entry->next;
            
            // Finally update this
            entry->size = size;
        }
        

        return (void*) (entry + 1);
    }
}

void* mem_alloc_calloc(size_t nmemb, size_t size) {
    void* ret = mem_alloc_malloc(size * nmemb);
    fnk_memops_memset(ret, 0, size * nmemb);
    return ret;
}

void* mem_alloc_realloc(void* b, size_t size) {
    // This is all one continuous operation so we can just do a memcpy on the zombie memory
    void* ret = mem_alloc_malloc(size);
    fnk_memops_memcpy(ret, b, size);
    return ret;
}

void mem_alloc_free(void* ptr) {
    struct mem_alloc_heap_entry* entry = ((struct mem_alloc_heap_entry*) ptr) - 1;
    
    // This finds the in between element so we can insert it sorted
    struct mem_alloc_heap_entry* prev = NULL;
    if (heap_head != NULL) {
        for (
            struct mem_alloc_heap_entry* e = heap_head;
            e != NULL && e > entry;
            prev = e, e = e->next
        );
    }

    if (prev != NULL) {
        // Insert after
        entry->next = prev->next;
        prev->next = entry;
    } else {
        // Insert to front
        entry->next = heap_head;
        heap_head = entry;
    }
    
    inc_coalesce();
}

void mem_alloc_fini() {
    mem_alloc_heap_start = NULL;
    heap_head = NULL;
}