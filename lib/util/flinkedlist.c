#include "lib/util/flinkedlist.h"
#include "types.h"

void util_flinkedlist_init(struct util_flinkedlist* list, size_t size) {
    if (size <= 1)
        return;

    // struct util_flinkedlist* prev = NULL;
    list[0].next = 1;
    list[0].prev = 0;
    for (unsigned i = 1; i < size - 1; i++) {
        list[i].next = i + 1;
        list[i].prev = i - 1;
    }
    list[size - 1].next = 0;
}

size_t util_flinkedlist_insert(struct util_flinkedlist* list, size_t node) {
    return list[node].next;
}

size_t util_flinkedlist_remove(struct util_flinkedlist* list, size_t node, size_t target) {
    list[list[target].prev].next = list[target].next;
    list[list[target].next].prev = list[target].prev;

    list[list[node].prev].next = target;
    list[target].prev = list[node].prev;
    list[target].next = node;

    return target;
}

size_t util_flinkedlist_getnext(struct util_flinkedlist* list, size_t node) {
    return list[node].next;
}