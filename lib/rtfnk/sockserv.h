/**
 * @file sockserv.h
 * @brief Internal sockserv things
 */

#ifndef LIB_RTFNK_SOCKSERV_H_
#define LIB_RTFNK_SOCKSERV_H_

#include "include/rtfnk/socketd.h"

typedef struct fnk_sockserv {
    // Each socket is serviced by popping it off the queue and then appending it to the back
    struct fnk_socket* head;
    struct fnk_socket* tail;
} fnk_sockserv_t;

#endif