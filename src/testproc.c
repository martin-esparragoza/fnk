#include "../include/rtfnk/proc.h"
#include "../include/rtfnk/pcb.h"
#include "../lib/util/flinkedlist.h"
    #include <stdio.h>

struct fnk_pcb* self;

/**
 * It is assumed that ALL programs will use a calling convention for the main function that treats its arguments as strictly on the stack
 */
int main(struct fnk_pcb* argself) {
    // Store them
    self = argself;

    /*while (1) {
        // Do something!
        fnk_proc_yield(self);
    }*/

    return 0;
}