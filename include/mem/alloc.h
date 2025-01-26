/**
 * @file alloc.h
 * @brief Memory allocations (pretty much just the heap)
 * 
 * This will be used for the system wide heap (reallocated when jump occours) <br>
 * Generally, errors "can't" occour because of how raw and unchecked this heap is
 */

#ifndef INCLUDE_MEM_ALLOC_H_
#define INCLUDE_MEM_ALLOC_H_

#include <stddef.h>
#include <stdint.h>

/**
 * @def MEM_ALLOC_OPS_BEFORE_COALESCE
 * @brief Number of ops before running a coalesce on the heap
 * 
 * Can't be defined before the file cuz its a static library :( <br>
 * A.K.A change it here
 */
#define MEM_ALLOC_FREES_BEFORE_COALESCE 3

/**
 * @brief Inits the heap
 *
 * Makes the head heap entry
 * 
 * @return Errc
 */
void mem_alloc_init();

/**
 * @brief Allocates a portion of memory on heap
 *
 * @param size Desired allocated length
 * 
 * @return Allocated memory
 */
void* mem_alloc_malloc(size_t size);

/**
 * @brief Allocates a portion of memory on the heap and writes a value to all of it
 *
 * @param value Value to write
 * @param size Desired allocated length
 * 
 * @return Allocated memory
 */
void* mem_alloc_calloc(uint64_t value, size_t size);

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