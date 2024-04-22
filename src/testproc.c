#include "../include/rtfnk/proc.h"
#include "../include/rtfnk/pcb.h"

unsigned int proc;
struct fnk_pcb* pcbs;
struct fnk_pcb* self;

/**
 * It is assumed that ALL programs will use a calling convention for the main function that treats its arguments as strictly on the stack
 */
int main(unsigned int argproc, struct fnk_pcb argpcbs[]) {
    // Store them
    proc = argproc;
    pcbs = argpcbs;

    self = &(pcbs[proc]);

    while (1) {
        // Do something!
        fnk_proc_yield(self);
    }

    return 1;
}
