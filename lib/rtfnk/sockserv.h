/**
 * @file sockserv.h
 * @brief Internal sockserv things
 */

#ifndef LIB_RTFNK_SOCKSERV_H_
#define LIB_RTFNK_SOCKSERV_H_

#include "../../include/rtfnk/sockserv.h"
#include "socket.h"
#include "../util/flinkedlist.h"

#define FNK_SOCKSRV_MAXSOCKETS 256

// Right now its literally just an array but I'd like to give flexibility
struct fnk_sockserv {
    struct util_flinkedlist sockets[FNK_SOCKSRV_MAXSOCKETS];
    struct util_flinkedlist* node;
};

#endif