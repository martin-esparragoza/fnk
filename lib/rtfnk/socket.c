/**
 * @file socket.c
 * @brief Buffer read/write handler
 */

#include "../include/rtfnk/socket.h"
#include "rtfnk/socket.h"
#include "util/flinkedlist.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

const char* fnk_socket_errctostr_def(int errc) {
    if (errc < sizeof(fnk_socket_def_errcstr) / sizeof(fnk_socket_def_errcstr[0]) && errc > 0)
        return fnk_socket_def_errcstr[errc];

    // Default errc not found
    return NULL;
}

int fnk_socket_write(struct fnk_socket* self, unsigned char* buf, size_t len) {
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

int fnk_socket_read(struct fnk_socket* self, unsigned char* buf, size_t len);