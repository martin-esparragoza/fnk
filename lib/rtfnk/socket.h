/**
 * @file socket.h
 * Private methods
 */

#ifndef LIB_RTFNK_SOCKET_H_
#define LIB_RTFNK_SOCKET_H_

#include "../../include/rtfnk/socket.h"
#include "../util/flinkedlist.h"

struct fnk_socket {
    unsigned char *const writebuffer; ///< Information that is to be written
    unsigned char *const readbuffer; ///< Information that has been read and is stored
    size_t writelen;
    size_t readlen;
    size_t writep; ///< P is for position
    size_t readp;
    struct util_flinkedlist* node;
};

#endif
