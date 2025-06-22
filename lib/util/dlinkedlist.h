/**
 * @brief Stupid doubly linked list
 * It is not circular! It has an END!
 */

#ifndef LIB_UTIL_DLINKEDLIST_H_
#define LIB_UTIL_DLINKEDLIST_H_

typedef struct util_dlinkedlist {
    struct util_dlinkedlist* prev;
    struct util_dlinkedlist* next;
    void* data; ///< Util is only for internal crap so I will unsafely use everything!
} util_dlinkedlist_t;

/**
 * @brief Zeroing constructor
 * If an element is going to be added immedietly, you shouldn't init it because all the values are just going to be set a 2nd time
 */
void util_dlinkedlist_init(struct util_dlinkedlist* elem);

/**
 * @brief Add in front of dll
 *
 * @param elem Thing to add in front of
 * @param newel New element to add
 */
void util_dlinkedlist_append(struct util_dlinkedlist* elem, struct util_dlinkedlist* newel);

/**
 * @brief Remove that element from the dll
 *
 * @return The element that was removed
 */
struct util_dlinkedlist* util_dlinkedlist_remove(struct util_dlinkedlist* elem);

void* util_dlinkedlist_getdata(const struct util_dlinkedlist* elem);

void util_dlinkedlist_setdata(struct util_dlinkedlist* elem, void* data);

#endif