#include "attr.h"
#include "config.h"
#include "types.h"
#define _GNU_SOURCE
#include <sys/mman.h>
#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PMEM_SIZE 1024 * 32 /* 32kb */
#define NO_OS_ERROR() printf("Error in entry.\n")
    // Just some error that can be executed without fnk and other libs being loaded

// Why externs to essentially pass function args? Because an entry that is able to include and call libraries is morally wrong

// All of these are just implemented in main
// I don't want to create a header because that's just odd
extern COMP_ATTR__NORETURN__ void main(void);
extern COMP_ATTR__NORETURN__ void errorhang(void);

// extern void* mem_alloc_heap_start;

// Ideally linking allows you to link this file together with the rest of the bootloader
// This then allows for these addreses above to resolve properly

int COMP_ATTR__NORETURN__ entry(void) {
    // Allocate a large block of memory for heap/stack
    //void* pmem = mmap(NULL, PMEM_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, /* discardable values */ -1, 0);
    
    
    void* pmem = malloc(PMEM_SIZE);

    if (pmem == NULL) {
        NO_OS_ERROR();
        errorhang();
    }
    
    // Create new context to launch emu
    ucontext_t context;
    getcontext(&context);
    
    // Stack direction down and heap direction up
    context.uc_stack.ss_sp = (void*) (((uintptr_t) pmem) + PMEM_SIZE) - 256; // Avoid zero page
    // mem_alloc_heap_start = pmem;

    context.uc_stack.ss_size = PMEM_SIZE;
    context.uc_stack.ss_flags = 0; // Use ss stack
    context.uc_link = NULL; // Noreturn

    makecontext(&context, main, 0);

    setcontext(&context); // Context switch will then set stack
}