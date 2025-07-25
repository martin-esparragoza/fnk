/**
 * @file alloc.h
 * @brief Memory allocations (pretty much just the heap)
 * 
 * This will be used for the system wide heap (reallocated when jump occours) <br>
 * Generally, errors "can't" occour because of how raw and unchecked this heap is
 */

#ifndef INCLUDE_MEM_ALLOC_H_
#define INCLUDE_MEM_ALLOC_H_

#include "types.h"

/**
 * @brief Inits the heap
 *
 * Makes the head heap entry
 * 
 * @param coalescing_max # of ops (free) before running a coalesce. Who came first, the chicken or the egg?
 */
void mem_alloc_init(unsigned char coalescing_max);

/**
 * @brief Allocates a portion of memory on heap
 *
 * @param size Desired allocated length
 * 
 * @return Allocated memory
 */
void* mem_alloc_malloc(size_t size);

/**
 * @brief Allocates a portion of memory on the heap and writes 0 to all of it
 *
 * @param nmemb Number of members
 * @param size Desired allocated length
 * 
 * @return Allocated memory
 */
void* mem_alloc_calloc(size_t nmemb, size_t size);

/**
 * @brief Reallocates a portion of memory on the heap to another size
 * 
 * New is padded with 0s
 *
 * @param ptr Pointer to buffer to reallocate
 * @param size New size
 * 
 * @return Allocated memory
 */
void* mem_alloc_realloc(void* ptr, size_t size);

/**
 * @brief Deallocates a portion of memory on the heap
 *
 * @param ptr Pointer to buffer to free
 */
void mem_alloc_free(void* ptr);

/**
 * Uninitialize the heap
 */
void mem_alloc_fini();

#endif