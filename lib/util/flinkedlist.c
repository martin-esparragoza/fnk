#include "flinkedlist.h"
#include <stddef.h>

void util_flinkedlist_init(struct util_flinkedlist* list, size_t size) {
    if (size <= 1)
        return;

    struct util_flinkedlist* prev = NULL;
    list[0].next = list + 1;
    list[0].prev = NULL;
    for (unsigned i = 1; i < size - 1; i++) {
        list[i].next = list + i + 1;
        list[i].prev = list + i - 1;
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
    target->prev->next = target->next;
    target->next->prev = target->prev;

    node->prev->next = target;
    target->prev = node->prev;
    target->next = node;

    return target;
}
