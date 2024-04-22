/**
 * @file socket.h
 * Private methods
 */

#pragma once
#include "../../include/rtfnk/socket.h"

/**
 * Set the (internal to the os) sockets pointer. Will be called by sockman
 */
void fnk_socket_setsocket(struct fnk_socket* _sockets[]);
