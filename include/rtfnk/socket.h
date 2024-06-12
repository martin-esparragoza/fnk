/**
 * @file socket.h
 * @brief Buffer read/write handler
 */

#ifndef INCLUDE_RTFNK_SOCKET_H_
#define INCLUDE_RTFNK_SOCKET_H_

#include <stddef.h>
#include <stdbool.h>

// No enums, I'd like the control the type
#define FNK_SOCKET_ERRC_DEF_OK 0
#define FNK_SOCKET_ERRC_DEF_BIND_WOULDOVERFLOW 1
#define FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW 2

// TODO const char*
const char* fnk_socket_def_errcstr[] = { ///< Default error codes to string (driver programs, reference this!)
    [FNK_SOCKET_ERRC_DEF_OK] = "[DEFAULT] Ok",
    [FNK_SOCKET_ERRC_DEF_BIND_WOULDOVERFLOW] = "[DEFAULT] No room in server to add new sockets",
    [FNK_SOCKET_ERRC_DEF_RW_WOULDOVERFLOW] = "[DEFAULT] Attempted to write/read outside buffer",
};

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
const char* fnk_socket_errctostr_def(unsigned char errc);

/**
 * @brief Write content to buffer
 *
 * Used in native endianness
 *
 * @param self Socket
 * @param buf  Buffer to read from
 * @param len  # of bytes to read
 */
unsigned char fnk_socket_write(struct fnk_socket* self, unsigned char* buf, size_t len);

/**
 * @brief Read content from buffer
 *
 * Used in native endianness
 *
 * @param self Socket
 * @param buf  Buffer to write to
 * @param len  # of bytes to write
 */
unsigned char fnk_socket_read(struct fnk_socket* self, unsigned char* buf, size_t len);

#endif