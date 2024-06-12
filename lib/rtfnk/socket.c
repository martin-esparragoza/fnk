/**
 * @file socket.c
 * @brief Buffer read/write handler
 */

#include "../../include/rtfnk/socket.h"
#include "socket.h"
#include "../util/flinkedlist.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

unsigned char fnk_socket_write(struct fnk_socket* self, unsigned char* buf, size_t len) {
    if (len + self->writep > self->writelen)
        return FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW;

    unsigned char padding = ((uintptr_t) buf) % 8;

    // Write until buffer reaches nice bit allignment
    for (unsigned i = 0; i < padding && i < len; i++) {
        *(self->writebuffer + self->writep++) = buf[i];
    }

    // Now write as largest possible
    for (unsigned i = 0; i < (len - padding) % 8; i++) {
        *((unsigned long long*) (self->writebuffer + self->writep)) = ((unsigned long long*) buf)[i];
        self->writep += 8;
    }

    return FNK_SOCKET_ERRC_DEF_OK;
}

unsigned char fnk_socket_read(struct fnk_socket* self, unsigned char* buf, size_t len);