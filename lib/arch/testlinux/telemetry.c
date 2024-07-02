#include "../../../include/sdrive/telemetry.h"
#include <stdio.h>
#include <stdarg.h>

int sdrive_telemetry_init() {
    return 0;
}

int sdrive_telemetry_fini() {
    return 0;
}

int sdrive_telemetry_puts(const char* str) {
    return puts(str);
}

int sdrive_telemetry_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vfprintf(stdout, format, args);
    va_end(args);
    return ret;
}