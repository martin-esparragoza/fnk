/**
 * @file sockservd.h
 * @brief Socket server definitions
 */

#ifndef DLL_FNK_INCLUDE_SOCKSERVD_H_
#define DLL_FNK_INCLUDE_SOCKSERVD_H_

#define FNK_SOCKSERV_ERRC_COULD_NOT_REMOVE_SOCKET COMMON_ERRC_BASE + 0
#define FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW COMMON_ERRC_BASE + 1
#define FNK_SOCKSERV_ERRC_NO_SOCKETS_BOUND COMMON_ERRC_BASE + 2

struct fnk_sockserv;
typedef struct fnk_sockserv fnk_sockserv_t;

#endif