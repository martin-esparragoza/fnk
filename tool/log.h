/**
 * @file log.h
 * @brief Header only logging file
 */

#ifndef TOOL_LOG_H_
#define TOOL_LOG_H_

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

#define LOG_LOGLEVEL_INFO 0
#define LOG_LOGLEVEL_WARNING 1
#define LOG_LOGLEVEL_ERROR 2
#define LOG_LOGLEVEL_BASE 2

static const char* log_loglevel_label_def[] = {
    [LOG_LOGLEVEL_INFO] = "INFO",
    [LOG_LOGLEVEL_WARNING] = "WARN",
    [LOG_LOGLEVEL_ERROR] = "ERRR"
};
extern const char* log_loglevel_label_alt[];
extern size_t log_loglevel_label_alt_sizeof; // Expected # of indexes

static const char* log_loglevel_label_unrecognized = "URECLVL";

typedef struct log_logger {
    FILE* dest;
} log_logger_t;

/**
 * @brief Create a new logger
 * @note Just sets the dest
 * @param [in] logger Logger target
 * @param [in] dest Output of the logger
 */
void log_logger_init(struct log_logger* logger, FILE* dest) {
    logger->dest = dest;
}

// Hack because they do the exact same thing
#define log_logger_setdest log_logger_init

/**
 * @brief Output a log message
 * @param [in] logger Logger target
 * @param [in] level Level to use. Can be user defined with alt
 * @param [in] format printf format
 */
void log_logger_log(struct log_logger* logger, unsigned char level, const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    // Get the coresponding string
    const char* label = log_loglevel_label_unrecognized;
    if (level < sizeof(log_loglevel_label_def) / sizeof(log_loglevel_label_def[0])) {
        label = log_loglevel_label_def[level];
    } else if (level < log_loglevel_label_alt_sizeof) {
        label = log_loglevel_label_alt[level];
    }

    fprintf(logger->dest, "[%s] ", label);
    vfprintf(logger->dest, format, args);

    va_end(args);
}

#endif