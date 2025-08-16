#include "dll/fnk/lib/sockserv.h"
#include "dll/fnk/lib/socket.h"
#include "dll/fnk/include/sockservd.h"
#include "dll/fnk/include/sockservf.h"
#include "common/include/errc.h"
#include "types.h"
#include "attr.h"

const char* errcstr[] = {
    [FNK_SOCKSERV_ERRC_NO_SOCKETS_BOUND - COMMON_ERRC_BASE] = "No sockets are bound to the server",
    [FNK_SOCKSERV_ERRC_COULD_NOT_REMOVE_SOCKET - COMMON_ERRC_BASE] = "Can't remove a socket that is not bound",
    [FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW - COMMON_ERRC_BASE] = "Attempted to write/read outside buffer"
};

void fnk_sockserv_init(struct fnk_sockserv* serv) {
    serv->head = serv->tail = NULL;
}

const char* fnk_sockserv_errctostr(unsigned errc) {
    if (errc > COMMON_ERRC_BASE) {
        errc -= COMMON_ERRC_BASE;
        if (errc < sizeof(errcstr) / sizeof(errcstr[0]))
            return errcstr[errc];
        // No error code was found
        return NULL;
    }
    return "Ok";
}

size_t fnk_sockserv_sizeof(void) {
    return sizeof(struct fnk_sockserv);
}

unsigned fnk_sockserv_getnextinqueue(struct fnk_sockserv* serv, struct fnk_socket** socket) {
    if (serv->tail == NULL)
        return FNK_SOCKSERV_ERRC_NO_SOCKETS_BOUND;
    *socket = serv->tail->next = serv->head;
    serv->tail = serv->head; // Oder of opps
    serv->head = serv->head->next;
    serv->tail->next = NULL;
    return 0;
}

void fnk_sockserv_bind(struct fnk_sockserv* serv, struct fnk_socket* socket) {
    if (serv->tail == NULL) {
        serv->head = serv->tail = socket;
    } else {
        serv->tail->next = socket;
        socket->next = NULL;
        serv->tail = socket;
    }
}

unsigned fnk_sockserv_remove(struct fnk_sockserv* serv, struct fnk_socket* socket) {
    if (socket == serv->head)
        serv->head = socket->next;

    // Iterate and remove (tail edge case works
    struct fnk_socket* prev = serv->head;
    for (struct fnk_socket* i = prev->next; i->next != 0; prev = i, i = i->next) {
        if (i == socket) { // Pop ts
            prev->next = i->next;
            return 0;
        }
    }
    return FNK_SOCKSERV_ERRC_COULD_NOT_REMOVE_SOCKET;
}

unsigned fnk_sockserv_readwritebuffer(struct fnk_socket* socket, void* dest, size_t len) {
    if (fnk_circularbuffer_read(&socket->writeb, dest, len)) {
        return FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW;
    }
    return 0;
}

unsigned fnk_sockserv_writereadbuffer(struct fnk_socket* socket, const void* src, size_t len) {
    if (fnk_circularbuffer_write(&socket->readb, src, len)) {
        return FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW;
    }
    return 0;
}