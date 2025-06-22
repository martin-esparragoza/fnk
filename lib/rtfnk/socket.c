/**
 * @file socket.c
 * @brief Buffer read/write handler
 */

#include "include/rtfnk/socket.h"
#include "lib/rtfnk/socket.h"
#include "lib/util/circularbuffer.h"
#include "types.h"

static const char* fnk_socket_def_errcstr[] = { ///< Default error codes to string (driver programs, reference this!)
    [FNK_SOCKET_ERRC_DEF_OK] = "Ok",
    [FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW] = "Attempted to write/read outside buffer",
};

void fnk_socket_init(struct fnk_socket* socket, void* readb, size_t readlen, void* writeb, size_t writelen) {
    util_circularbuffer_init(&socket->readb, readb, readlen);
    util_circularbuffer_init(&socket->writeb, writeb, writelen);
}

const char* fnk_socket_errctostr_def(int errc) {
    if (errc < sizeof(fnk_socket_def_errcstr) / sizeof(fnk_socket_def_errcstr[0]) && errc >= 0)
        return fnk_socket_def_errcstr[errc];

    // Default errc not found
    return NULL;
}

int fnk_socket_write(struct fnk_socket* socket, const void* buf, size_t len) {
    if (util_circularbuffer_write(&socket->writeb, buf, len)) {
        return FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW;
    }
    return FNK_SOCKET_ERRC_DEF_OK;
}

// Implementation wise yeah I guess you do want to kind of spam this until you have necessary data. Yield if you're in userland ya stupid idiot
int fnk_socket_read(struct fnk_socket* socket, void* buf, size_t len) {
    if (util_circularbuffer_read(&socket->readb, buf, len)) {
        return FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW;
    }
    return FNK_SOCKET_ERRC_DEF_OK;
}