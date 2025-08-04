// TODO: Very unsafely written. I don't like this

#include "lib/util/dlinkedlist.h"
#include "types.h"

void util_dlinkedlist_init(struct util_dlinkedlist* elem) {
    elem->prev = elem->next = elem->data = NULL;
}

void util_dlinkedlist_append(struct util_dlinkedlist* elem, struct util_dlinkedlist* newel) {
    elem->next = newel;
    newel->prev = elem;
}

struct util_dlinkedlist* util_dlinkedlist_remove(struct util_dlinkedlist* elem) {
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    return elem;
}

void* util_dlinkedlist_getdata(const struct util_dlinkedlist* elem) {
    return elem->data;
}

void util_dlinkedlist_setdata(struct util_dlinkedlist* elem, void* data) {
    elem->data = data;
}