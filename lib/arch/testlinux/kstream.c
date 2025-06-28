/**
 * @file kstream.c
 * Read in kernel via an astract socket
 */

#include "include/sdrive/kstream.h"
#include "include/rtfnk/socket.h"
#include "include/rtfnk/sockserv.h"
#include "include/mem/alloc.h"
#include "types.h"
#include <stdio.h>

typedef struct sdrive_kstream_ctx {
    unsigned requested_bytes;
} sdrive_kstream_ctx_t;

#define SDRIVE_KSTREAM_ERRC_FILE_NOT_FOUND 1

static struct fnk_sockserv* server;
static FILE* fp;

static const char* errcstr[] = { ///< Default error codes to string (driver programs, reference this!)
    [SDRIVE_KSTREAM_ERRC_OK] = "Ok",
    [SDRIVE_KSTREAM_ERRC_FILE_NOT_FOUND] = "No kernel file found",
};

int sdrive_kstream_init() {
    server = mem_alloc_malloc(fnk_sockserv_sizeof());
    fnk_sockserv_init(server);
    fp = fopen("test.img", "a");
    fclose(fp);
    fp = fopen("test.img", "rb+");
    return SDRIVE_KSTREAM_ERRC_OK;
}

int sdrive_kstream_fini() {
    fclose(fp);
    return SDRIVE_KSTREAM_ERRC_OK;
}

const char* sdrive_kstream_errctostr(int errc) {
    if (errc < sizeof(errcstr) / sizeof(errcstr[0]) && errc >= 0)
        return errcstr[errc];

    // Default errc not found
    return NULL;
}

inline size_t sdrive_kstream_ctx_sizeof() {
    return sizeof(struct sdrive_kstream_ctx);
}

int sdrive_kstream_ctx_init(struct sdrive_kstream_ctx* ctx) {
    ctx->requested_bytes = 0;
    return SDRIVE_KSTREAM_ERRC_OK;
}

int sdrive_kstream_ctx_fini(struct sdrive_kstream_ctx* ctx) {
    return SDRIVE_KSTREAM_ERRC_OK;
}

int sdrive_kstream_bind(struct fnk_socket* socket) {
    fnk_sockserv_bind(server, socket);
    return SDRIVE_KSTREAM_ERRC_OK;
}

int sdrive_kstream_remove(struct fnk_socket* socket) {
    return fnk_sockserv_remove(server, socket);
}

void sdrive_kstream_requestdata(struct fnk_socket* socket, size_t length) {
    struct sdrive_kstream_ctx* ctx = fnk_socket_getctx(socket);
    ctx->requested_bytes = length;
}

int sdrive_kstream_update() {
    // Update a singlar socket

    struct fnk_socket* sock;
    int errc = SDRIVE_KSTREAM_ERRC_OK;
    if ((errc = fnk_sockserv_getnextinqueue(server, &sock)) != FNK_SOCKSERV_ERRC_OK)
        return errc;

    struct sdrive_kstream_ctx* ctx = fnk_socket_getctx(sock);

    if (ctx->requested_bytes != 0) {
        unsigned char buf[ctx->requested_bytes];
        fread(buf, 1, ctx->requested_bytes, fp);
        if ((errc = fnk_sockserv_writereadbuffer(sock, buf, ctx->requested_bytes)) != FNK_SOCKSERV_ERRC_OK)
            return errc;
        ctx->requested_bytes = 0;
    }

    return SDRIVE_KSTREAM_ERRC_OK;
}