// TODO: This file needs to incorporate direct memory transfers to do stuff faster if necessary
// Future martin here. Maybe??? Idk it doesnt seem that necessary...

#include "dll/fnk/lib/circularbuffer.h"
#include "common/include/memops.h"
#include "types.h"

void fnk_circularbuffer_init(struct fnk_circularbuffer* cbuf, void* allocated, size_t length) {
    cbuf->buffer = allocated;
    cbuf->len = length;
    cbuf->writei = cbuf->readi = 0;
}

unsigned fnk_circularbuffer_write(struct fnk_circularbuffer* cbuf, const void* src, size_t length) {
    // First we need to check if we can hold the required buffer
    
    // Space variables..
    size_t used, free, free_until_wrap;
    if (cbuf->writei >= cbuf->readi) {
        used = cbuf->writei - cbuf->readi;
        free_until_wrap = cbuf->len - cbuf->writei;
    } else {
        used = cbuf->len - cbuf->readi + cbuf->writei;
        free_until_wrap = cbuf->readi - cbuf->writei; // You can do like a little optimization here and just do the memcpy without checking if it would wrap
        // But I'm lazy and this code is slightly elegant
    }
    free = cbuf->len - used - 1;

    if (free < length)
        return true;

    // Now that we have everything mapped out its just a matter of memcpys
    if (length >= free_until_wrap) {
        common_memops_memcpy(cbuf->buffer + cbuf->writei, src, free_until_wrap);
        src += free_until_wrap;
        buf->writei = length - free_until_wrap;
        common_memops_memcpy(cbuf->buffer, src, cbuf->writei);
    } else {
        common_memops_memcpy(cbuf->buffer + cbuf->writei, src, length);
        cbuf->writei += length;
    }

    return false;
}

unsigned fnk_circularbuffer_read(struct fnk_circularbuffer* cbuf, void* dest, size_t length) {
    // Sort of the same thing as the last function

    // Yet again define some space variables
    size_t used, used_until_wrap;
    if (cbuf->writei >= cbuf->readi) {
        used = used_until_wrap = cbuf->writei - cbuf->readi;
    } else {
        used = cbuf->len - cbuf->readi + cbuf->writei;
        used_until_wrap = cbuf->len - cbuf->readi;
    }

    if (used < length)
        return true;

    if (length > used_until_wrap) {
        common_memops_memcpy(dest, cbuf->buffer + cbuf->readi, used_until_wrap);
        dest += used_until_wrap;
        buf->readi = 0;
        common_memops_memcpy(dest, cbuf->buffer, length - used_until_wrap);
    } else {
        common_memops_memcpy(dest, cbuf->buffer + cbuf->readi, length);
    }
    cbuf->readi = (cbuf->readi + length) % cbuf->len;

    return false;
}

inline bool fnk_circularbuffer_isempty(const struct fnk_circularbuffer* cbuf) {
    return cbuf->readi == cbuf->writei;
}

inline bool fnk_circularbuffer_isfull(const struct fnk_circularbuffer* cbuf) {
    return ((cbuf->writei + 1) % cbuf->len) == cbuf->readi;
}

inline size_t fnk_circularbuffer_getlen(const struct fnk_circularbuffer* cbuf) {
    return circularbuffer->len;
}

inline size_t fnk_circularbuffer_getused(const struct fnk_circularbuffer* cbuf) {
    return cbuf->writei >= cbuf->readi ?
        cbuf->writei - cbuf->readi :
        cbuf->len - cbuf->readi + cbuf->writei;
}