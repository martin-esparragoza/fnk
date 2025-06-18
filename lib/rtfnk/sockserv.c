#include "lib/rtfnk/sockserv.h"
#include "include/rtfnk/sockserv.h"
#include "lib/rtfnk/socket.h"
#include "lib/util/flinkedlist.h"

/*void fnk_sockserv_init(struct fnk_sockserv* self) {
    util_flinkedlist_init(self->ll, FNK_SOCKSRV_MAXSOCKETS);
    self->node = 0;
}

int fnk_sockserv_bind(struct fnk_sockserv* self, struct fnk_socket* socket) {
    size_t node = util_flinkedlist_insert(self->ll, self->node);
    // BAD.
    if (!node)
        return FNK_SOCKET_ERRC_DEF_BIND_WOULDOVERFLOW;
    self->sockets[node] = socket;
    self->node = socket->node = node;
    return FNK_SOCKET_ERRC_DEF_OK;
}

void fnk_sockserv_remove(struct fnk_sockserv* self, struct fnk_socket* socket) {
    util_flinkedlist_remove(self->ll, self->node, socket->node);
}*/