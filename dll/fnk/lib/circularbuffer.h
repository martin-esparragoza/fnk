#ifndef DLL_FNK_LIB_CIRCULARBUFFER_H_
#define DLL_FNK_LIB_CIRCULARBUFFER_H_

#include "types.h"

typedef struct fnk_circularbuffer {
    unsigned char* buffer; // I'd like for this to be a *const, however with this targeting multiple compilers I can't be reliant on returning a structure in the constructor function
    size_t len;
    size_t writei;
    size_t readi;
} fnk_circularbuffer_t;

/**
 * @brief Instantiate a new circular buffer 
 * @note Actual size is length - 1 because 1 buffer is reserved
 * @param [in] cbuf Object to create
 * @param [in] buffer Actual data buffer allocated by user
 * @param [in] length Length in bytes of the allocated buffer
 */
void fnk_circularbuffer_init(struct fnk_circularbuffer* cbuf, void* allocated, size_t length);

/**
 * @brief Write to circular buffer
 * @note Weird retval stuff because there can only be 1 possible error and its a private function
 * @param [in] cbuf Circular buffer object
 * @param [in] buffer Data to be written to the circualr buffer
 * @param [in] length # of bytes to write
 * @retval false If success
 * @retval true If could not write data to buffer (buffer would overflow)
 */
unsigned fnk_circularbuffer_write(struct fnk_circularbuffer* cbuf, const void* buffer, size_t length);

/**
 * @brief Read from circular buffer
 * @note Weird retval stuff because there can only be 1 possible error and its a private function
 * @param [in] cbuf Circular buffer object
 * @param [out] buffer Data to be coppied to from circular buffer
 * @param [in] length # of bytes to 
 * @retval false If success
 * @retval true If could not write data to buffer (buffer would overflow)
 */
unsigned fnk_circularbuffer_read(struct fnk_circularbuffer* cbuf, void* buffer, size_t length);

/**
 * @brief Checks if the circular buffer is empty
 * @param [in] cbuf Circular buffer object
 * @return true if empty
 * @return false if full
 */
bool fnk_circularbuffer_isempty(const struct fnk_circularbuffer* cbuf);

/**
 * @brief Checks if the circular buffer is full
 * @param [in] cbuf Circular buffer object
 * @return true if full
 * @return false if empty
 */
bool fnk_circularbuffer_isfull(const struct fnk_circularbuffer* cbuf);

/**
 * @brief Returns the total length of the circular buffer
 * @param [in] cbuf Circular buffer object
 * @return Size of the circular buffer in bytes
 */
size_t fnk_circularbuffer_getlen(const struct fnk_circularbuffer* cbuf);

/**
 * @brief Returns the # of occupied in the circular buffer
 * @param [in] circularbuffer Circular buffer object
 * @return # of bytes occupied in the circular buffer
 */
size_t fnk_circularbuffer_getused(const struct fnk_circularbuffer* cbuf);

#endif