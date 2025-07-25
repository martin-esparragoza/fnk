#include "lib/rtfnk/sockserv.h"
#include "lib/rtfnk/socket.h"
#include "include/rtfnk/sockservf.h"
#include "include/rtfnk/sockservd.h"
#include "include/rtfnk/socketf.h"
#include "include/rtfnk/socketd.h"
#include "types.h"

static const char* errcstr[] = {
    [FNK_SOCKSERV_ERRC_OK] = "Ok",
    [FNK_SOCKSERV_ERRC_NO_SOCKETS_BOUND] = "No sockets are bound to the server",
    [FNK_SOCKSERV_ERRC_COULD_NOT_REMOVE_SOCKET] = "Can't remove a socket that is not bound",
    [FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW] = "Attempted to write/read outside buffer"
};

void fnk_sockserv_init(struct fnk_sockserv* serv) {
    serv->head = serv->tail = NULL;
}

inline size_t fnk_sockserv_sizeof() {
    return sizeof(struct fnk_sockserv);
}

const char* fnk_sockserv_errctostr(int errc) {
    if (errc < sizeof(errcstr) / sizeof(errcstr[0]) && errc >= 0)
        return errcstr[errc];

    return NULL;
}

int fnk_sockserv_getnextinqueue(struct fnk_sockserv* serv, struct fnk_socket** socket) {
    if (serv->tail == NULL)
        return FNK_SOCKSERV_ERRC_NO_SOCKETS_BOUND;
    *socket = serv->tail->next = serv->head;
    serv->tail = serv->head; // Oder of opps
    serv->head = serv->head->next;
    serv->tail->next = NULL;
    return FNK_SOCKSERV_ERRC_OK;
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

int fnk_sockserv_remove(struct fnk_sockserv* serv, struct fnk_socket* socket) {
    if (socket == serv->head)
        serv->head = socket->next;

    // Iterate and remove (tail edge case works
    struct fnk_socket* prev = serv->head;
    for (struct fnk_socket* i = prev->next; i->next != 0; prev = i, i = i->next) {
        if (i == socket) { // Pop ts
            prev->next = i->next;
            return FNK_SOCKSERV_ERRC_OK;
        }
    }
    return FNK_SOCKSERV_ERRC_COULD_NOT_REMOVE_SOCKET;
}

int fnk_sockserv_readwritebuffer(struct fnk_socket* socket, void* dest, size_t len) {
    if (util_circularbuffer_read(&socket->writeb, dest, len)) {
        return FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW;
    }
    return FNK_SOCKSERV_ERRC_OK;
}

int fnk_sockserv_writereadbuffer(struct fnk_socket* socket, const void* src, size_t len) {
    if (util_circularbuffer_write(&socket->readb, src, len)) {
        return FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW;
    }
    return FNK_SOCKSERV_ERRC_OK;
}