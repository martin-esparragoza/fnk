#include "lib/util/dlinkedlist.h"

inline void util_dlinkedlist_init(struct util_dlinkedlist* elem) {
    elem->prev = elem->next = elem->data = 0;
}

void util_dlinkedlist_append(struct util_dlinkedlist* elem, struct util_dlinkedlist* newel) {
    elem->next = newel;
    newel->prev = elem;
}

struct util_dlinkedlist* util_dlinkedlist_remove(struct util_dlinkedlist* elem) {
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
}