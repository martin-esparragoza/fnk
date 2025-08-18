/**
 * @file log.h
 * @brief Logging file
 */

#ifndef ELFTOFNK_INCLUDE_LOG_H_
#define ELFTOFNK_INCLUDE_LOG_H_

#include <stdio.h>
#include <stdarg.h>

#define ELFTOFNK_LOG_LEVEL_INFO 0
#define ELFTOFNK_LOG_LEVEL_WARNING 1
#define ELFTOFNK_LOG_LEVEL_ERROR 2
#define ELFTOFNK_LOG_LEVEL_BASE 2

typedef struct elftofnk_log {
    FILE* dest;
} elftofnk_log_t;

/**
 * @brief Create a new logger
 * @note Just sets the dest
 * @param [in] log Logger target
 * @param [in] dest Output of the logger
 */
void elftofnk_log_init(struct elftofnk_log* log, FILE* dest);

// Hack because they do the exact same thing
#define elftofnk_log_setdest elftofnk_log_init

/**
 * @brief Outputs a lot message given va_list
 * @param [in] log Logger target
 * @param [in] level Level to use. Can be used defined with altarr
 * @param [in] format printf format
 * @param [in] args va_list of arguments
 */
void elftofnk_logvf(struct elftofnk_log* log, unsigned char level, const char* format, va_list args);

/**
 * @brief Output a log message. Much more user friendly
 * @param [in] logger Logger target
 * @param [in] level Level to use. Can be user defined with altarr
 * @param [in] format printf format
 */
void elftofnk_logf(struct elftofnk_log_logger* logger, unsigned char level, const char* format, ...);

#define ELFTOFNK_LOG_INFO(format, ...) elftofnk_logf(&logger, ELFTOFNK_LOG_LEVEL_INFO, format, ## __VA_ARGS__)
#define ELFTOFNK_LOG_WARN(format, ...) elftofnk_logf(&logger, ELFTOFNK_LOG_LEVEL_WARNING, format, ## __VA_ARGS__)
#define ELFTOFNK_LOG_ERRR(format, ...) elftofnk_logf(&logger, ELFTOFNK_LOG_LEVEL_ERROR, format, ## __VA_ARGS__)

#endif