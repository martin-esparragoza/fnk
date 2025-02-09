/**
 * @file sockserv.h
 * @brief Internal sockserv things
 */

#ifndef LIB_RTFNK_SOCKSERV_H_
#define LIB_RTFNK_SOCKSERV_H_

#include "include/rtfnk/sockserv.h"
#include "lib/rtfnk/socket.h"
#include "lib/util/flinkedlist.h"
#include "types.h"

#define FNK_SOCKSRV_MAXSOCKETS 256

// Right now its literally just an array but I'd like to give flexibility
struct fnk_sockserv {
    struct util_flinkedlist ll[FNK_SOCKSRV_MAXSOCKETS];
    struct fnk_socket* sockets[FNK_SOCKSRV_MAXSOCKETS];
    size_t node;
};

#endif