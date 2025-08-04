/**
 * @file pjddef.h
 * @brief Program jump descriptor definition
 */

#ifndef DLL_FNK_INCLUDE_PJDDEF_H_
#define DLL_FNK_INCLUDE_PJDDEF_H_

#include "common/include/pjd.h"
#include "dll/fnk/include/socketf.h"
#include "dll/fnk/include/socketservf.h"
#include "attr.h"
#include "types.h"

COMP_ATTR__USED__ COMP_ATTR__SECTION__(".pjds") struct common_pjd fnk_pjd {
   .name = "fnk",
}

void (*fnk_socket_init)(
    struct fnk_socket*,
    void*,
    size_t,
    void*,
    size_t
) = fnk_pjd.functions[0];
const char* (*fnk_socket_errctostr)(
    unsigned
) = fnk_pjd.functions[1];
size_t (*fnk_socket_sizeof)(
    void
) = fnk_pjd.functions[2];
void (*fnk_socket_attachctx)(
    struct fnk_socket*,
    void*
) = fnk_pjd.functions[3];
unsigned (*fnk_socket_write)(
    struct fnk_socket*,
    const void*,
    size_t,
    size_t**
) = fnk_pjd.functions[4]
unsigned (*fnk_socket_read)(
    struct fnk_socket*,
    void*,
    size_t
) = fnk_pjd.functions[5];
size_t (*fnk_socket_getreadlen)(
    struct fnk_socket*
) = fnk_pjd.functions[6];
size_t (*fnk_socket_getwritelen)(
    struct fnk_socket*
) = fnk_pjd.functions[7];
void* (*fnk_socket_getctx)(
    struct fnk_socket*
) = fnk_pjd.functions[8];
void (*fnk_sockserv_init)(
    struct fnk_sockserv*
) = fnk_pjd.functions[9];
const char* (*fnk_sockserv_errctostr)(
    unsigned
) = fnk_pjd.functions[10];
size_t (*fnk_sockserv_sizeof)(
    void
) = fnk_pjd.functions[11];
unsigned (*fnk_sockserv_getnextinqueue)(
    struct fnk_sockserv*,
    struct fnk_socket**
) = fnk_pjd.functions[12];
void (*fnk_sockserv_bind)(
    struct fnk_sockserv*,
    struct fnk_socket*
) = fnk_pjd.functions[13];
unsigned (*fnk_sockserv_remove)(
    struct fnk_sockserv*,
    struct fnk_socket*
) = fnk_pjd.functions[14];
unsigned (*fnk_sockserv_readwritebuffer)(
    struct fnk_socket*,
    void*,
    size_t
) = fnk_pjd.functions[15];
unsigned (*fnk_sockserv_writereadbuffer)(
    struct fnk_socket*,
    const void*,
    size_t
) = fnk_pjd.functions[16];

#endif