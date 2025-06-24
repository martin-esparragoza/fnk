#include "lib/util/circularbuffer.h"
#include "include/rtfnk/memops.h"
#include "types.h"


void util_circularbuffer_init(struct util_circularbuffer* buf, void* allocated, size_t length) {
    buf->buffer = allocated;
    buf->len = length;
    buf->writei = buf->readi = 0;
}

int util_circularbuffer_write(struct util_circularbuffer* buf, const void* src, size_t length) {
    // First we need to check if we can hold the required buffer
    
    // Space variables..
    size_t used, free, free_until_wrap;
    if (buf->writei >= buf->readi) {
        used = buf->writei - buf->readi;
        free_until_wrap = buf->len - buf->writei;
    } else {
        used = buf->len - buf->readi + buf->writei;
        free_until_wrap = buf->readi - buf->writei; // You can do like a little optimization here and just do the memcpy without checking if it would wrap
        // But I'm lazy and this code is slightly elegant
    }
    free = buf->len - used - 1;

    if (free < length)
        return -1;

    // Now that we have everything mapped out its just a matter of memcpys
    if (length >= free_until_wrap) {
        fnk_memops_memcpy(buf->buffer + buf->writei, src, free_until_wrap);
        src += free_until_wrap;
        buf->writei = length - free_until_wrap;
        fnk_memops_memcpy(buf->buffer, src, buf->writei);
    } else {
        fnk_memops_memcpy(buf->buffer + buf->writei, src, length);
        buf->writei += length;
    }

    return 0;
}

int util_circularbuffer_read(struct util_circularbuffer* buf, void* dest, size_t length) {
    // Sort of the same thing as the last function

    // Yet again define some space variables
    size_t used, used_until_wrap;
    if (buf->writei >= buf->readi) {
        used = used_until_wrap = buf->writei - buf->readi;
    } else {
        used = buf->len - buf->readi + buf->writei;
        used_until_wrap = buf->len - buf->readi;
    }

    if (used < length)
        return -1;

    if (length > used_until_wrap) {
        fnk_memops_memcpy(dest, buf->buffer + buf->readi, used_until_wrap);
        dest += used_until_wrap;
        buf->readi = 0;
        fnk_memops_memcpy(dest, buf->buffer, length - used_until_wrap);
    } else {
        fnk_memops_memcpy(dest, buf->buffer + buf->readi, length);
    }
    buf->readi = (buf->readi + length) % buf->len;

    return 0;
}

inline bool util_circularbuffer_isempty(const struct util_circularbuffer* buf) {
    return buf->readi == buf->writei;
}

inline bool util_circularbuffer_isfull(const struct util_circularbuffer* buf) {
    return ((buf->writei + 1) % buf->len) == buf->readi;
}

inline size_t util_circularbuffer_getlen(const struct util_circularbuffer* buf) {
    return buf->len;
}

inline size_t util_circularbuffer_getused(const struct util_circularbuffer* buf) {
    return buf->writei >= buf->readi ? buf->writei - buf->readi : buf->len - buf->readi + buf->writei;
}