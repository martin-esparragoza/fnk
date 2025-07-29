#include "boot/include/telemetry.h"
#include <stdio.h>
#include <stdarg.h>

unsigned boot_telemetry_init(void) {
    return 0;
}

unsigned boot_telemetry_fini(void) {
    return 0;
}

unsigned boot_telemetry_puts(const char* str) {
    return puts(str);
}

unsigned boot_telemetry_putc(char c) {
    return putc(c, stdout);
}

unsigned boot_telemetry_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vfprintf(stdout, format, args);
    va_end(args);
    return ret;
}