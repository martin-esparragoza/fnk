/**
 * @file socket.h
 * @brief Buffer read/write handler
 */

#ifndef INCLUDE_RTFNK_SOCKET_H_
#define INCLUDE_RTFNK_SOCKET_H_

#include "types.h"

// No enums, I'd like the control the type
#define FNK_SOCKET_ERRC_DEF_OK 0
#define FNK_SOCKET_ERRC_DEF_BIND_WOULDOVERFLOW 1
#define FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW 2

struct fnk_socket;
typedef struct fnk_socket fnk_socket_t;

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
 * @brief Write content to buffer
 *
 * Used in native endianness
 *
 * @param self Socket
 * @param buf  Buffer to read from
 * @param len  # of bytes to read
 * @return # of bytes written
 */
int fnk_socket_write(struct fnk_socket* self, unsigned char* buf, size_t len);

/**
 * @brief Read content from buffer
 *
 * Used in native endianness
 *
 * @param self Socket
 * @param buf Buffer to write to
 * @param len  # of bytes to write
 * @return # of bytes read
 */
int fnk_socket_read(struct fnk_socket* self, unsigned char* buf, size_t len);

#endif