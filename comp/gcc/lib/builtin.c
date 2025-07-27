#include "types.h"
#include "common/include/memops.h"

// STRONG
uint16_t fnk_memops_bswap16(uint16_t data) {
    return __builtin_bswap16(data);
}

// STRONG
uint32_t fnk_memops_bswap32(uint32_t data) {
    return __builtin_bswap32(data);
}

// STRONG
uint64_t fnk_memops_bswap64(uint64_t data) {
    return __builtin_bswap64(data);
}