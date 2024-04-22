/**
 * @file socket.h
 * Private methods
 */

#pragma once
#include "../../include/rtfnk/socket.h"

/**
 * Set the sockets pointer. Will be called by sockman
 */
void fnk_socket_setsocket(struct fnk_socket* _sockets[]);
