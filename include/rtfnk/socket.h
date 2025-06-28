/**
 * @file socket.h
 * @brief Buffer read/write handler
 */

#ifndef INCLUDE_RTFNK_SOCKET_H_
#define INCLUDE_RTFNK_SOCKET_H_

#include "types.h"

// No enums, I'd like the control the type
#define FNK_SOCKET_ERRC_DEF_OK 0
#define FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW 1

struct fnk_socket;
typedef struct fnk_socket fnk_socket_t;

/**
 * @brief Create a new socket (unbinded)
 *
 * @param socket Object
 * @param readb Pointer to read buffer
 * @param readlen Length of read buffer
 * @param writeb Pointer to write buffer
 * @param writelen Length of write buffer
 */
void fnk_socket_init(struct fnk_socket* socket, void* readb, size_t readlen, void* writeb, size_t writelen);

/**
 * @brief Convert errc to string
 *
 * Must be a DEFAULT error code otherwise will return NULL
 *
 * @param errc Error code
 * @return String and if cannot find returns NULL
 */
const char* fnk_socket_errctostr_def(int errc);

/**
 * @brief To allocate the element
 */
size_t fnk_socket_sizeof();

/**
 * @brief Sets the context of a socket (a lot of drivers need this)
 */
void fnk_socket_attachctx(struct fnk_socket* socket, void* ctx);

/**
 * @brief Write content to buffer
 *
 * Used in native endianness
 *
 * @param socket Socket
 * @param buf   Buffer to read from
 * @param len   # of bytes to read
 * @return      # of bytes written
 */
int fnk_socket_write(struct fnk_socket* socket, const void* buf, size_t len);

/**
 * @brief Read content from buffer
 *
 * Used in native endianness
 *
 * @param socket Socket
 * @param buf   Buffer to write to
 * @param len   # of bytes to write
 * @return      # of bytes read
 */
int fnk_socket_read(struct fnk_socket* socket, void* buf, size_t len);

size_t fnk_socket_getreadlen(struct fnk_socket* socket);

size_t fnk_socket_getwritelen(struct fnk_socket* socket);

void* fnk_socket_getctx(struct fnk_socket* socket);

#endif