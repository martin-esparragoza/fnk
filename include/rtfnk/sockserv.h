/**
 * @file sockserv.h
 * @brief Socket server for driver processes
 */

#ifndef INCLUDE_RTFNK_SOCKSERV_H_
#define INCLUDE_RTFNK_SOCKSERV_H_

#include "include/rtfnk/socket.h"
#include "types.h"

#define FNK_SOCKSERV_ERRC_OK 0
#define FNK_SOCKSERV_ERRC_COULD_NOT_REMOVE_SOCKET 1
#define FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW 2
#define FNK_SOCKSERV_ERRC_NO_SOCKETS_BOUND 3

struct fnk_sockserv;
typedef struct fnk_sockserv fnk_sockserv_t;

/**
 * @brief Constructor
 */
void fnk_sockserv_init(struct fnk_sockserv* serv);

/**
 * @brief Gets the next socket in queue (and puts it at the back)
 *
 * @param serv Server
 * @param socket Output
 */
int fnk_sockserv_getnextinqueue(struct fnk_sockserv* serv, struct fnk_socket** socket);

/**
 * @brief Adds the socket to the server
 */
void fnk_sockserv_bind(struct fnk_sockserv* serv, struct fnk_socket* socket);

/**
 * @brief Removes the socket from the server
 * The kernel will not clean your stuff up! Clean it up yourself or risk memory leakage!
 */
int fnk_sockserv_remove(struct fnk_sockserv* serv, struct fnk_socket* socket);

/**
 * @brief Server level reading of the write buffer
 *
 * @param dest Buffer to write into
 * @param len # of bytes to read
 */
int fnk_sockserv_readwritebuffer(struct fnk_socket* socket, void* dest, size_t len);

/**
 * @brief Server level writing to the read buffer
 *
 * @param dest Buffer to read from
 * @param len # of bytes to write
 */
 int fnk_sockserv_writereadbuffer(struct fnk_socket* socket, void* src, size_t len);

#endif