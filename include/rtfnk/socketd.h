/**
 * @file socket.h
 * @brief Buffer read/write handler
 * Only the defintions
 */

#ifndef INCLUDE_RTFNK_SOCKETD_H_
#define INCLUDE_RTFNK_SOCKETD_H_

#define FNK_SOCKET_ERRC_DEF_OK 0
#define FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW 1

struct fnk_socket;
typedef struct fnk_socket fnk_socket_t;

#endif