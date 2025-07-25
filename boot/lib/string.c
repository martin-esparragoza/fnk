#include "lib/util/string.h"
#include "types.h"

size_t util_strlen(const char* str) {
    size_t i = 0;
    for (; str[i] != '\0'; i++);
    return i;
}