#include "dll/fnk/include/socketf.h"
#include "dll/fnk/include/socketd.h"
#include "dll/fnk/lib/socket.h"
#include "dll/fnk/lib/circularbuffer.h"
#include "common/include/errc.h"
#include "types.h"
#include "attr.h"

// So it doesn't get put into .data because .data is discarded
COMP_ATTR__SECTION__(".text") static const char* errcstr[] = {
    [FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW - COMMON_ERRC_BASE] = "Attempted to write/read outside buffer",
    [FNK_SOCKET_ERRC_NO_FREE_MAILBOXES - COMMON_ERRC_BASE] = "No space to add mailbox entry"
};

void fnk_socket_init(struct fnk_socket* socket, void* readb, size_t readlen, void* writeb, size_t writelen) {
    fnk_circularbuffer_init(&socket->readb, readb, readlen);
    fnk_circularbuffer_init(&socket->writeb, writeb, writelen);
    socket->next = socket->ctx = NULL;
}

const char* fnk_socket_errctostr(unsigned errc) {
    if (errc > 0) {
        if (errc < sizeof(errcstr) / sizeof(errcstr[0]))
            return errcstr[errc - COMMON_ERRC_BASE];
        // No error code was found
        return NULL;
    }
    return "Ok";
}

inline size_t fnk_socket_sizeof(void) {
    return sizeof(struct fnk_socket);
}

void fnk_socket_attachctx(struct fnk_socket* socket, void* ctx) {
    socket->ctx = ctx;
}

unsigned fnk_socket_write(struct fnk_socket* socket, const void* buf, size_t len, size_t* entry) {
    // Check if we have a valid mailbox entry O(N) but N should be super small so its fine]
    // Esp. because the bulk of the processing should be copying the data
    size_t i = 0;
    for (; i < FNK_SOCKET_MBOX_COUNT; i++) {
        if (socket->mbox[i] == SFNK_SOCKET_MBOX_STATUS_OPEN) {
            *entry = i;
            break;
        }
    }
    
    // There are no valid mailboxes
    if (i == FNK_SOCKET_MBOX_COUNT)
        return FNK_SOCKET_ERRC_NO_FREE_MAILBOXES;

    if (fnk_circularbuffer_write(&socket->writeb, buf, len))
        return FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW;
    return 0;
}

// Implementation wise yeah I guess you do want to kind of spam this until you have necessary data. Yield if you're in userland ya stupid idiot
unsigned fnk_socket_read(struct fnk_socket* socket, void* buf, size_t len) {
    if (fnk_circularbuffer_read(&socket->readb, buf, len))
        return FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW;
    return 0;
}

inline size_t fnk_socket_getreadlen(struct fnk_socket* socket) {
    return fnk_circularbuffer_getused(&socket->readb);
}

inline size_t fnk_socket_getwritelen(struct fnk_socket* socket) {
    return fnk_circularbuffer_getused(&socket->writeb);
}

inline void* fnk_socket_getctx(struct fnk_socket* socket) {
    return socket->ctx;
}