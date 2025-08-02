#include "common/include/fnkconfig.h"
#include "socketf.h"
#include "sockservf.h"
#include "attr.h"
#include "types.h"

// Remember, you have a hard limit of 32
COMP_ATTR__USED__ COMP_ATTR__SECTION__(".ljd") static uintptr_t ljd[COMMON_FNKCONFIG_MAX_LIBFUNCTIONS] = {
   (uintptr_t) fnk_socket_init,
   (uintptr_t) fnk_socket_errctostr,
   (uintptr_t) fnk_socket_sizeof,
   (uintptr_t) fnk_socket_attachctx,
   (uintptr_t) fnk_socket_write,
   (uintptr_t) fnk_socket_read,
   (uintptr_t) fnk_socket_getreadlen,
   (uintptr_t) fnk_socket_getwritelen,
   (uintptr_t) fnk_socket_getctx,
   (uintptr_t) fnk_sockserv_init,
   (uintptr_t) fnk_sockserv_errctostr,
   (uintptr_t) fnk_sockserv_sizeof,
   (uintptr_t) fnk_sockserv_getnextinqueue,
   (uintptr_t) fnk_sockserv_bind,
   (uintptr_t) fnk_sockserv_remove,
   (uintptr_t) fnk_sockserv_readwritebuffer,
   (uintptr_t) fnk_sockserv_writereadbuffer
};