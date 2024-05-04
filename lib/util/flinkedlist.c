#include "flinkedlist.h"
#include <stddef.h>

void util_flinkedlist_init(struct util_flinkedlist* list, size_t size) {
    if (size <= 1)
        return;

    for (unsigned i = 0; i < size - 1; i++) {
        list[i].next = &(list[i + 1]);
    }
    list[size - 1].next = 0;
}

struct util_flinkedlist* util_flinkedlist_insert(struct util_flinkedlist* node, void* data) {
    if (!node->next) // We can't add to the linkedlist
        return NULL;

    node->data = data;
    return node->next;
}

struct util_flinkedlist* util_flinkedlist_remove(struct util_flinkedlist* node, struct util_flinkedlist* target) {
    target->next = node;
    return target;
}
