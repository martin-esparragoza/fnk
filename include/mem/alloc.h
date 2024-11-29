/**
 * @file alloc.h
 * @brief Memory allocations (pretty much just the heap)
 * 
 * This will be used for the system wide heap (reallocated when jump occours)
 */

#ifndef INCLUDE_MEM_ALLOC_H_
#define INCLUDE_MEM_ALLOC_H_

#include <stddef.h>
#include <stdint.h>

#define MEM_ALLOC_ERRC_OK 0
#define MEM_ALLOC_ERRC_HEAP_INIT_FAIL 1
#define MEM_ALLOC_ERRC_HEAP_NO_SPACE 2

/**
 * @brief Inits the heap
 *
 * @return Errc
 */
int mem_alloc_init();

/**
 * @brief Returns a string coresponding to error code
 *
 * @param errc Error code
 */
const char* mem_alloc_errctostr(int errc);

/**
 * @brief Allocates a portion of memory on heap
 *
 * @param b Pointer to buffer ptr
 * @param size Desired allocated length
 * 
 * @return Error code
 */
int mem_alloc_malloc(void** b, size_t size);

/**
 * @brief Allocates a portion of memory on the heap and writes a value to all of it
 *
 * @param b Pointer to buffer ptr
 * @param value Value to write
 * @param size Desired allocated length
 * 
 * @return Error code
 */
int mem_alloc_calloc(void** b, uint64_t value, size_t size);

/**
 * @brief Reallocates a portion of memory on the heap to another size
 * 
 * New is padded with 0s
 *
 * @param ptr Pointer to buffer to reallocate
 * @param size New size
 */
int mem_alloc_realloc(void* ptr, size_t size);

/**
 * @brief Deallocates a portion of memory on the heap
 *
 * @param ptr Pointer to buffer to free
 */
int mem_alloc_free(void* ptr);

/**
 * Uninitialize the heap
 */
int mem_alloc_fini();

#endif