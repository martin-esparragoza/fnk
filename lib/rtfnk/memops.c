#include "include/rtfnk/memops.h"
#include "types.h"
#include "attr.h"

void COMP_ATTR__WEAK__ rtfnk_memops_bswap(void* data, size_t size) {
    uint8_t* p = data;

    for (size_t i = 0; i < size / 2; i++) {
        p[i] ^= p[size - i - 1];
        p[size - i - 1] ^= p[i];
        p[i] ^= p[size - i - 1];
    }
}

uint16_t COMP_ATTR__WEAK__ rtfnk_memops_bswap16(uint16_t data) {
    rtfnk_memops_bswap(&data, 2);
    return data;
}

uint32_t COMP_ATTR__WEAK__ rtfnk_memops_bswap32(uint32_t data) {
    rtfnk_memops_bswap(&data, 4);
    return data;
}

uint64_t COMP_ATTR__WEAK__ rtfnk_memops_bswap64(uint64_t data) {
    rtfnk_memops_bswap(&data, 8);
    return data;
}

uintptr_t COMP_ATTR__WEAK__ rtfnk_memops_align(uintptr_t value, int toalign) {
    return toalign - (value % toalign) + value;
}

void COMP_ATTR__WEAK__ rtfnk_memops_memcpy(void* dest, void* src, size_t length) {
    uintptr_t* dw = dest;
    uintptr_t* sw = src;
    
    for (; length >= sizeof(uintptr_t); length -= sizeof(uintptr_t))
        *(dw++) = *(sw++);

    for (uint8_t* db = (void*) dw, *sb = (void*) sw; length > 0; length--)
        *(db++) = *(sb++);
}

void COMP_ATTR__WEAK__ rtfnk_memops_memset(void* dest, uint8_t val, size_t length) {
    uintptr_t* dw = dest;
    
    // Create the val that is equivalent to multiple vals
    uintptr_t bigval = val;
    for (unsigned char i = 1; i < sizeof(uintptr_t); i++)
        bigval |= ((uintptr_t) val) << i * 8;
    
    for (; length >= sizeof(uintptr_t); length -= sizeof(uintptr_t))
        *(dw++) = bigval;

    for (uint8_t* db = (void*) dw; length > 0; length--)
        *(db++) = val;
}