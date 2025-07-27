#include "boot/include/telemetry.h"
#include <stdio.h>
#include <stdarg.h>

int boot_telemetry_init() {
    return 0;
}

int boot_telemetry_fini() {
    return 0;
}

int boot_telemetry_puts(const char* str) {
    return puts(str);
}

int boot_telemetry_putc(char c) {
    return putc(c, stdout);
}

int boot_telemetry_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vfprintf(stdout, format, args);
    va_end(args);
    return ret;
}