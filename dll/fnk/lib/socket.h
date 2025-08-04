/**
 * @file socket.h
 * Private socket definition that is not exposed to the user
 */

#ifndef DLL_FNK_LIB_SOCKET_H_
#define DLL_FNK_LIB_SOCKET_H_

#include "dll/fnk/include/socketd.h"
#include "dll/fnk/lib/circularbuffer.h"

typedef struct fnk_socket {
    struct fnk_circularbuffer writeb;
    struct fnk_circularbuffer readb;
    unsigned mbox[FNK_SOCKET_MBOX_COUNT];
    struct fnk_socket* next;
    void* ctx; // Unique variable that allows for a driver to keep track of necessary information
} fnk_socket_t;

#endif