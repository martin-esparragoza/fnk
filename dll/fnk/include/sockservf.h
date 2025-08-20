/**
 * @file sockservf.h
 * @brief Socket server functions
 */

#ifndef DLL_FNK_INCLUDE_SOCKSERVF_H_
#define DLL_FNK_INCLUDE_SOCKSERVF_H_

#include "dll/fnk/include/socketd.h"
#include "dll/fnk/include/sockservd.h"
#include "types.h"

/**
 * @brief Create a new socket server
 * @param [out] serv Server object to instantiate
 */
void fnk_sockserv_init(struct fnk_sockserv* serv);

/**
 * @brief Convert error code to string
 * @param [in] errc Error code
 * @return ptr
 * @retval NULL if cannot find
 */
const char* fnk_sockserv_errctostr(unsigned errc);

/**
 * @brief To allocate the element
 */
size_t fnk_sockserv_sizeof(void);

/**
 * @brief Gets the next socket to service in queue
 * @note Puts that socket to the back of the queue
 * @param [in] serv Server to take socket out of
 * @param [out] socket Will be set to pointer to new socket
 * @retval FNK_SOCKSERV_ERRC_NO_SOCKETS_BOUND if there are no sockets in queue
 * @retval 0 if everything went fine
 */
unsigned fnk_sockserv_getnextinqueue(struct fnk_sockserv* serv, struct fnk_socket** socket);

/**
 * @brief Adds the socket to the server
 * @param [in] serv Target server to bind to
 * @param [in] socket Socket to add to the server
 */
void fnk_sockserv_bind(struct fnk_sockserv* serv, struct fnk_socket* socket);

/**
 * @brief Removes the socket from the server (unbind)
 * @note The socket data is still fine just it is not attached to anything
 * @param [in] serv Server the socket belongs to
 * @param [in] socket Socket to unbind
 * @retval FNK_SOCKSERV_ERRC_COULD_NOT_REMOVE_SOCKET
 * @retval 0 If everything went fine
 */
unsigned fnk_sockserv_remove(struct fnk_sockserv* serv, struct fnk_socket* socket);

/**
 * @brief Server level reading of the write buffer from the socket
 * @note This is from user input often times
 * @param [in] socket Socket to read from
 * @param [out] dest Where the write buffer will be coppied to
 * @param [in] len # of bytes to read from the write buffer
 * @retval FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW
 * @retval 0 If everything went fine
 */
unsigned fnk_sockserv_readwritebuffer(struct fnk_socket* socket, void* dest, size_t len);

/**
 * @brief Server level writing to the read buffer of the socket
 * @note User will take this in as input (remember to set ur mailboxes!)
 * @param [in] socket Socket to write to
 * @param [in] dest Buffer with the target data to write
 * @param [in] len # of bytes to write to the socket
 * @retval FNK_SOCKSERV_ERRC_RW_WOULDOVERFLOW
 * @retval 0 If everything went fine
 */
unsigned fnk_sockserv_writereadbuffer(struct fnk_socket* socket, const void* src, size_t len);

#endif