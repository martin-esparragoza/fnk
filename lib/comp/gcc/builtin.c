#include "types.h"
#include "lib/util/ops.h"

uint16_t util_ops_bswap16(uint16_t data) {
    return __builtin_bswap16(data);
}

uint32_t util_ops_bswap32(uint32_t data) {
    return __builtin_bswap32(data);
}

uint64_t util_ops_bswap64(uint64_t data) {
    return __builtin_bswap64(data);
}