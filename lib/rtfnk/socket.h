/**
 * @file socket.h
 * Private methods
 */

#ifndef LIB_RTFNK_SOCKET_H_
#define LIB_RTFNK_SOCKET_H_

#include "include/rtfnk/socketd.h"
#include "lib/util/circularbuffer.h"
#include "types.h"

struct fnk_socket {
    struct util_circularbuffer writeb;
    struct util_circularbuffer readb;
    struct fnk_socket* next;
    void* ctx; // Unique variable that allows for a driver to keep track of necessary information
};

#endif
