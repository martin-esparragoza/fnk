#include "types.h"
#include "include/rtfnk/memops.h"

uint16_t fnk_memops_bswap16(uint16_t data) {
    return __builtin_bswap16(data);
}

uint32_t fnk_memops_bswap32(uint32_t data) {
    return __builtin_bswap32(data);
}

uint64_t fnk_memops_bswap64(uint64_t data) {
    return __builtin_bswap64(data);
}