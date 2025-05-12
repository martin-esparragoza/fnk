#include "lib/util/ops.h"
#include "types.h"
#include "attr.h"

// TODO: Function definition

void COMP_ATTR__WEAK__ util_ops_bswap(void* data, size_t size) {
    uint8_t* p = data;

    for (size_t i = 0; i < size / 2; i++) {
        p[i] ^= p[size - i - 1];
        p[size - i - 1] ^= p[i];
        p[i] ^= p[size - i - 1];
    }
}

uint16_t COMP_ATTR__WEAK__ util_ops_bswap16(uint16_t data) {
    util_ops_bswap(&data, 2);
    return data;
}

uint32_t COMP_ATTR__WEAK__ util_ops_bswap32(uint32_t data) {
    util_ops_bswap(&data, 4);
    return data;
}

uint64_t COMP_ATTR__WEAK__ util_ops_bswap64(uint64_t data) {
    util_ops_bswap(&data, 8);
    return data;
}


bool COMP_ATTR__WEAK__ util_ops_ispowertwo(unsigned x) {
    return x && !(x & (x - 1));
}

int COMP_ATTR__WEAK__ util_ops_min(int a, int b) {
    return a > b ? b : a;
}

int COMP_ATTR__WEAK__ util_ops_max(int a, int b) {
    return a > b ? a : b;
}

uintptr_t COMP_ATTR__WEAK__ align(uintptr_t value, int toalign) {
    return toalign - (value % toalign) + value;
}

void COMP_ATTR__WEAK__ memcpy(void* dest, void* src, size_t length) {
}

void COMP_ATTR__WEAK__ memset(void* dest, char c, size_t length) {
}

//#include "builtin.h"