#include "lib/util/mem.h"
#include "types.h"
#include "attr.h"

void COMP_ATTR__WEAK__ util_mem_bswap(void* data, size_t size) {
    uint8_t* p = data;

    for (size_t i = 0; i < size / 2; i++) {
        p[i] ^= p[size - i - 1];
        p[size - i - 1] ^= p[i];
        p[i] ^= p[size - i - 1];
    }
}

uint16_t COMP_ATTR__WEAK__ util_mem_bswap16(uint16_t data) {
    util_mem_bswap(&data, 2);
    return data;
}

uint32_t COMP_ATTR__WEAK__ util_mem_bswap32(uint32_t data) {
    util_mem_bswap(&data, 4);
    return data;
}

uint64_t COMP_ATTR__WEAK__ util_mem_bswap64(uint64_t data) {
    util_mem_bswap(&data, 8);
    return data;
}

uintptr_t COMP_ATTR__WEAK__ util_mem_align(uintptr_t value, int toalign) {
    return toalign - (value % toalign) + value;
}

// Changing this file and recompiling does nothing unless you clean? TODO:
void COMP_ATTR__WEAK__ util_mem_memcpy(void* dest, void* src, size_t length) {
    unsigned* dw = dest;
    unsigned* sw = src;
    
    for (; length >= sizeof(int); length -= sizeof(int))
        *(dw++) = *(sw++);

    for (uint8_t* db = (void*) dw, *sb = (void*) sw; length > 0; length--)
        *(db++) = *(sb++);
}

void COMP_ATTR__WEAK__ util_mem_memset(void* dest, uint8_t val, size_t length) {
    unsigned* dw = dest;
    
    // Create the val that is equivalent to multiple vals
    unsigned  bigval = val;
    for (unsigned char i = 1; i < sizeof(int); i++)
        bigval |= ((unsigned) val) << i * 8;
    
    for (; length >= sizeof(int); length -= sizeof(int))
        *(dw++) = bigval;

    for (uint8_t* db = (void*) dw; length > 0; length--)
        *(db++) = val;
}