/**
 * @file flinkedlist.h
 * @brief Fixed size linked list
 * This means that the linked list relies on the fact of the linked list already being fully assembled and then rearrangeable
 * Doubly linked
 */

#ifndef LIB_UTIL_FLINKEDLIST_H_
#define LIB_UTIL_FLINKEDLIST_H_

#include <stddef.h>

typedef struct util_flinkedlist {
    void* data;
    struct util_flinkedlist* next;
    struct util_flinkedlist* prev;
} util_flinkedlist_t;

/**
 * @brief Inits linkedlist data to be proper
 * @param list Table of all elements in the linkedlist
 * Sets each element in the linked list to point to the next (excluding the last)
 */
void util_flinkedlist_init(struct util_flinkedlist* list, size_t size);

/**
 * @brief Inserts a new element into the linked list at the top
 *
 * @param node Last node returned
 *
 * @return Next available node NULL if can't insert one
 */
struct util_flinkedlist* util_flinkedlist_insert(struct util_flinkedlist* node, void* data);

/**
 * @brief Remove that node
 *
 * @param node Last node returned
 * @param target Node to remove
 * @return Next available node
 */
struct util_flinkedlist* util_flinkedlist_remove(struct util_flinkedlist* node, struct util_flinkedlist* target);

#endif
