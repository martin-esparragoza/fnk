/**
 * @file socket.h
 * Private methods
 */

#ifndef LIB_RTFNK_SOCKET_H_
#define LIB_RTFNK_SOCKET_H_

#include "include/rtfnk/socket.h"
#include "lib/util/circularbuffer.h"
#include "types.h"

struct fnk_socket {
    struct util_circularbuffer writeb;
    struct util_circularbuffer readb;
};

#endif
