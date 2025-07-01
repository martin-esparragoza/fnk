/**
 * @file sockserv.h
 * @brief Socket server for driver processes
 * Only the definitions
 */

#ifndef INCLUDE_RTFNK_SOCKSERVD_H_
#define INCLUDE_RTFNK_SOCKSERVD_H_

#define FNK_SOCKSERV_ERRC_OK 0
#define FNK_SOCKSERV_ERRC_COULD_NOT_REMOVE_SOCKET 1
#define FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW 2
#define FNK_SOCKSERV_ERRC_NO_SOCKETS_BOUND 3

struct fnk_sockserv;
typedef struct fnk_sockserv fnk_sockserv_t;

#endif