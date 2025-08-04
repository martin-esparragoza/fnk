/**
 * @file socketf.h
 * @brief Buffer read/write handler
 * @note Function definitions
 */

#ifndef DLL_FNK_INCLUDE_SOCKETF_H_
#define DLL_FNK_INCLUDE_SOCKETF_H_

#include "dll/fnk/include/socketd.h"
#include "types.h"

/**
 * @brief Create a new socket
 * @note Is not bound
 *
 * @param [out] socket Object to instantiate
 * @param [in] readp Read buffer
 * @param [in] readlen Length of read buffer
 * @param [in] writeb Write buffer
 * @param [in] writelen Length of write buffer
 */
void fnk_socket_init(struct fnk_socket* socket, void* readb, size_t readlen, void* writeb, size_t writelen);

/**
 * @brief Convert returned error code to string
 * @param [in] errc Returned error code
 * @return Error string pointer
 * @retval NULL if cannot be found
 */
const char* fnk_socket_errctostr(unsigned errc);

/**
 * @brief To allocate the object
 */
size_t fnk_socket_sizeof(void);

/**
 * @brief Attaches driver context to a socket (extra stuff to convey info)
 * @param [in] socket Target socket to attach
 * @param [in] ctx Pointer to generic context object
 */
void fnk_socket_attachctx(struct fnk_socket* socket, void* ctx);

/**
 * @brief Write content from buffer
 * @note Native endianness.
 * @param [in] socket Target socket to write to
 * @param [in] buf Pointer to data buffer (read from)
 * @param [in] len # of bytes to write
 * @param [out] entry If the write succeded, entry will be set to a new mailbox entry to reference
 * @return Error code
 * @retval 0 if everything went good
 * Once you have a mailbox entry, you should only be reading it and wait for it
 * to reach your desired state or error. After that you must relieve the mailbox
 * of its duties by setting it to FNK_SOCKET_MBOX_STATUS_FREE which allows for
 * other processes to use it.
 */
unsigned fnk_socket_write(struct fnk_socket* socket, const void* buf, size_t len, unsigned** entry);

/**
 * @brief Read content to buffer
 * @note Native endianness.
 * @param [in] socket Target socket to read from
 * @param [out] buf Pointer to data buffer (written to)
 * @param [in] len # of bytes to read
 * @return Error code
 * @retval 0 if everything went good
 */
unsigned fnk_socket_read(struct fnk_socket* socket, void* buf, size_t len);

/**
 * @brief Get # of bytes used in the socket write buffer
 * @return Size in bytes
 */
size_t fnk_socket_getreadlen(struct fnk_socket* socket);

/**
 * @brief Get # of bytes used in the socket write buffer
 * @return Size in bytes
 */
size_t fnk_socket_getwritelen(struct fnk_socket* socket);

/**
 * @brief Returns the context object attached to the socket
 * @note NULL if socket has been instantiated and the context has not been set
 * @return NULL if none otherwise pointer
 */
void* fnk_socket_getctx(struct fnk_socket* socket);

#endif