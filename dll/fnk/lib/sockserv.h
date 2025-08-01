/**
 * @file sockserv.h
 * @brief Internal sockserv things
 */

#ifndef DLL_FNK_LIB_SOCKSERV_H_
#define DLL_FNK_LIB_SOCKSERV_H_

#include "dll/fnk/include/socketd.h"

typedef struct fnk_sockserv {
    // Each socket is serviced by popping it off the queue and then appending it to the back
    struct fnk_socket* head;
    struct fnk_socket* tail;
} fnk_sockserv_t;

#endif