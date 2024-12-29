#include "attr.h"
#include "config.h"
#define _GNU_SOURCE
#include <sys/mman.h>
#include <ucontext.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define PMEM_SIZE 1024 * 8 /* 8kb */
#define NO_OS_ERROR() printf("Error in entry.\n")
    // Just some error that can be executed without rtfnk and other libs being loaded

// Why externs to essentially pass function args? Because an entry that is able to include and call libraries is morally wrong

// All of these are just implemented in main
// I don't want to create a header because that's just odd
extern INCLUDE_COMP_ATTR_NORETURN void main();
extern INCLUDE_COMP_ATTR_NORETURN void errorhang();

extern void* mem_alloc_heap_start;

// Ideally linking allows you to link this file together with the rest of the bootloader
// This then allows for these addreses above to resolve properly

int INCLUDE_COMP_ATTR_NORETURN entry() {
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
    context.uc_stack.ss_sp = (void*) (((uintptr_t) pmem) + PMEM_SIZE);
    mem_alloc_heap_start = pmem;

    context.uc_stack.ss_size = PMEM_SIZE;
    context.uc_stack.ss_flags = 0; // Use ss stack
    context.uc_link = NULL; // Noreturn

    makecontext(&context, main, 0);

    setcontext(&context); // Context switch will then set stack
}