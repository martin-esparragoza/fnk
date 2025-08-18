#include "elftofnk/include/log.h"
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

static const char* level_label_def[] = {
    [ELFTOFNK_LOG_LEVEL_INFO] = "INFO",
    [ELFTOFNK_LOG_LEVEL_WARNING] = "WARN",
    [ELFTOFNK_LOG_LEVEL_ERROR] = "ERRR"
};
extern const char* elftofnk_log_level_label_alt[];
extern size_t elftofnk_log_level_label_alt_sizeof; // Expected # of indexes

static const char* level_label_unrecognized = "URECLVL";

void elftofnk_log_init(struct elftofnk_log* log, FILE* dest) {
    log->dest = dest;
}

void elftofnk_logvf(struct elftofnk_log* log, unsigned char level, const char* format, va_list args) {
    const char* label = level_label_unrecognized;
    if (level < sizeof(level_label_def) / sizeof(level_label_def[0])) {
        label = level_label_def[level];
    } else if (level < elftofnk_log_level_label_alt_sizeof) {
        label = elftofnk_log_level_label_alt[level];
    }

    fprintf(log->dest, "[%s] ", label);
    vfprintf(log->dest, format, args);
}

void elftofnk_logf(struct elftofnk_log* log, unsigned char level, const char* format, ...) {
    va_list args;
    va_start(args, format);
    elftofnk_logvf(log, level, format, args);
    va_end(args);
}