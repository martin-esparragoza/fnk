#include "attr.h"
#include "config.h"
#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>

#define PMEM_SIZE 1024 * 8 /* 8kb */
#define NO_OS_ERROR() printf("Error in entry.\n")
    // Just some error that can be executed without rtfnk and other libs being loaded

// All of these are just implemented in main
// I don't want to create a header because that's just odd
extern INCLUDE_COMP_ATTR_NORETURN int main();
extern INCLUDE_COMP_ATTR_NORETURN void errorhang();
extern void* mem_alloc_heap_start;

// Ideally linking allows you to link this file together with the rest of the bootloader
// This then allows for these addreses above to resolve properly

int INCLUDE_COMP_ATTR_NORETURN entry() {
    // Allocate a large block of memory for heap/stack
    void* pmem = mmap(NULL, PMEM_SIZE, PROT_READ | PROT_WRITE, MAP_ANON, /* discardable values */ -1, 0);

    if (pmem == MAP_FAILED) {
        NO_OS_ERROR();
        errorhang();
    }
    
    // Set respective stack and heap
#ifdef ARCH_CONFIG_STACK_DIR_DOWN
    mem_alloc_heap_start = pmem; // IMPORTANT: Load in before you do this stupid
#ifdef __x86_64__
    __asm__ volatile ("mov %0, %%rsp" : : "r"(((uintptr_t) pmem) + PMEM_SIZE));
#else
    __asm__ volatile ("mov %0, %%esp" : : "r"(((uintptr_t) pmem) + PMEM_SIZE));
#endif
#else
    mem_alloc_heap_start = ((uintptr_t) pmem) + PMEM_SIZE;
#ifdef __x86_64__
    __asm__ volatile ("mov %0, %%rsp" : : "r"(pmem));
#else
    __asm__ volatile ("mov %0, %%esp" : : "r"(pmem));
#endif
#endif
    
    main();
}