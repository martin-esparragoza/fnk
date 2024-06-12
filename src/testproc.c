#include "../include/rtfnk/proc.h"
#include "../include/rtfnk/pcb.h"
#include "../lib/util/flinkedlist.h"
    #include <stdio.h>

unsigned int proc;
struct fnk_pcb* self;
struct util_flinkedlist list[50];
struct util_flinkedlist* node;

/**
 * It is assumed that ALL programs will use a calling convention for the main function that treats its arguments as strictly on the stack
 */
int main(struct fnk_pcb* argself) {
    // Store them
    self = argself;

    util_flinkedlist_init(list, sizeof(list) / sizeof(list[0]));
    node = list;

    node = util_flinkedlist_insert(node, (void*) 0xAAAA);
    node = util_flinkedlist_insert(node, (void*) 0xBBBB);
    struct util_flinkedlist* n = node; // CCCC
    node = util_flinkedlist_insert(node, (void*) 0xCCCC);
    node = util_flinkedlist_insert(node, (void*) 0xDDDD);
    node = util_flinkedlist_insert(node, (void*) 0xEEEE);

    node = util_flinkedlist_remove(node, n);

    node = util_flinkedlist_insert(node, (void*) 0xDEADBEEF);

    printf("%x | %x | %x | %x\n", node->data, node, node->next, node->prev);
    for (struct util_flinkedlist* i = list; i != node; i = i->next) {
        printf("%x | %x | %x | %x\n", i->data, i, i->next, i->prev);
    }

    /*while (1) {
        // Do something!
        fnk_proc_yield(self);
    }*/

    return 0;
}
