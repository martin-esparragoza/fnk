/**
 * @file socketd.h
 * @brief Buffer read/write handler
 * @note Exposed definitions
 */

#ifndef DLL_FNK_INCLUDE_SOCKETD_H_
#define DLL_FNK_INCLUDE_SOCKETD_H_

#include "common/include/errc.h"

#define FNK_SOCKET_ERRC_RW_BUFFER_WOULD_OVERFLOW COMMON_ERRC_BASE + 0
#define FNK_SOCKET_ERRC_NO_FREE_MAILBOXES COMMON_ERRC_BASE + 1

#define FNK_SOCKET_MBOX_STATUS_FREE 0
#define FNK_SOCKET_MBOX_STATUS_WORKING 1

#define FNK_SOCKET_MBOX_COUNT 5

struct fnk_socket;
typedef struct fnk_socket fnk_socket_t;

#endif