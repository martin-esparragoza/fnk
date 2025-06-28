/**
 * @brief Kernel file stream
 *
 * The kernel could be located at different locations for each system. 
 * Because of this we have a standard stream that must be implemented
 */

#ifndef INCLUDE_SDRIVE_KSTREAM_H_
#define INCLUDE_SDRIVE_KSTREAM_H_

#include "include/rtfnk/socket.h"
#include "types.h"

struct sdrive_kstream_ctx;
typedef struct sdrive_kstream_ctx arch_kstream_ctx_t;

#define SDRIVE_KSTREAM_ERRC_OK 0

/**
 * Synchronous
 *
 * @return errc
 */
int sdrive_kstream_init();

/**
 * Synchronous
 *
 * @return errc
 */
int sdrive_kstream_fini();

/**
 * @return Pointer to string housing the error codu NULL if can't find one
 */
const char* sdrive_kstream_errctostr(int errc);

/**
 * @brief Used to allocate the kstream ctx
 *
 * Remember to attach this to your socket
 * If not unexpected behavior will happen
 */
size_t sdrive_kstream_ctx_sizeof();

/**
 * @brief Defaults
 */
int sdrive_kstream_ctx_init(struct sdrive_kstream_ctx* ctx);

/**
 * @brief In case your driver needs this
 */
int sdrive_kstream_ctx_fini(struct sdrive_kstream_ctx* ctx);

/**
 * @brief Adds the socket to the server
 * <b>Remember</b> to attach your context
 * @return errc
 */
int sdrive_kstream_bind(struct fnk_socket* socket);

/**
 * @brief Removes the socket from the server
 * @return errc
 */
int sdrive_kstream_remove(struct fnk_socket* socket);

/**
 * @brief Ask socket to produce data
 * Wait for the socket to have the right amount of data left in the buffer
 */
void sdrive_kstream_requestdata(struct fnk_socket* socket, size_t length);

/**
 * @return errc
 */
int sdrive_kstream_update();

#endif