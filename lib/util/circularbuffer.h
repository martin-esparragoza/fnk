#ifndef LIB_UTIL_CIRCULARBUFFER_H_
#define LIB_UTIL_CIRCULARBUFFER_H_

#include "types.h"

typedef struct util_circularbuffer {
    unsigned char* buffer; // I'd like for this to be a *const, however with this targeting multiple compilers I can't be reliant on returning a structure in the constructor function
    size_t len;
    size_t writei;
    size_t readi;
} util_circularbuffer_t;

/**
 * @brief Constructor
 *
 * @param buf Object
 * @param allocated Reserved section of memory for the circular buffer
 * @param length The entire length of the buffer. 1 byte is reserved so your TRUE buffer length is length - 1
 */
void util_circularbuffer_init(struct util_circularbuffer* buf, void* allocated, size_t length);

/**
 * @brief Write bytes from buf into the circular buffer
 *
 * @param buf Object
 * @param src Data to be written
 * @param length # of bytes to write
 *
 * @return -1 if buffer would overflow
 */
int util_circularbuffer_write(struct util_circularbuffer* buf, const void* src, size_t length);

/**
 * @brief Read bytes from buf into the dest ptr
 *
 * @param buf Object
 * @param dest Output data to be copied to
 * @param length # of bytes to read
 *
 * @return -1 if buffer would overflow
 */
int util_circularbuffer_read(struct util_circularbuffer* buf, void* dest, size_t length);

/**
 * @brief Checks if the circular buffer is empty
 *
 * @param buf Object
 *
 * @return 1 if empty
 */
bool util_circularbuffer_isempty(const struct util_circularbuffer* buf);

/**
 * @brief Checks if the circular buffer is full
 *
 * @param buf Object
 *
 * @return 1 if full
 */
bool util_circularbuffer_isfull(const struct util_circularbuffer* buf);

size_t util_circularbuffer_getlen(const struct util_circularbuffer* buf);

#endif