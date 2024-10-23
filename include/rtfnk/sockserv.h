/**
 * @file sockserv.h
 * @brief Socket server for driver processes
 */

#ifndef INCLUDE_RTFNK_SOCKSRV_H_
#define INCLUDE_RTFNK_SOCKSRV_H_

#include "include/rtfnk/socket.h"
#include <stdbool.h>

/**
 * 
 */
struct fnk_sockserv;
typedef struct fnk_sockserv fnk_sockserv_t;

/**
 * @brief Sets information to be proper
 */
void fnk_sockserv_init(struct fnk_sockserv* self);

/**
 * @brief Add socket to server
 */
int fnk_sockserv_bind(struct fnk_sockserv* self, struct fnk_socket* socket);

/**
 * @brief Remove socket from server
 * 
 * VERY IMPORTANT! PLEASE DO THIS!!
 */
void fnk_sockserv_remove(struct fnk_sockserv* self, struct fnk_socket* socket);

#endif