/**
 * @file telemetry.h
 * @brief Telemetry output (implementation of this can be skipped if desired)
 */

#ifndef INCLUDE_SDRIVE_TELEMETRY_H_
#define INCLUDE_SDRIVE_TELEMETRY_H_

#include "config.h"

/**
 * @brief Init telemetry before sending anything
 * @return Error code
 *
 * If this fails the code should still be able to run
 */
int sdrive_telemetry_init();

/**
 * @brief Remove telemetry stream
 */
int sdrive_telemetry_fini();

/**
 * @brief Put string
 */
int sdrive_telemetry_puts(const char* str);

/**
 * @brief Put character
 */
int sdrive_telemetry_putc(char c);

/**
 * @brief Put string to telemetry
 * @return Error code
 */
int sdrive_telemetry_printf(const char* format, ...);

#define SDRIVE_TELEMETRY_LOG(format, ...) sdrive_telemetry_printf("[%s:%d]" format, __FILE__, __LINE__, ## __VA_ARGS__)

#if ARCH_CONFIG_VERBOSE >= 3
#define SDRIVE_TELEMETRY_INF(format, ...) sdrive_telemetry_printf("[INF %s:%d]" format, __FILE__, __LINE__, ## __VA_ARGS__)
#else
#define SDRIVE_TELEMETRY_INF(format, ...)
#endif

#if ARCH_CONFIG_VERBOSE >= 2
#define SDRIVE_TELEMETRY_WRN(format, ...) sdrive_telemetry_printf("[WRN %s:%d]" format, __FILE__, __LINE__, ## __VA_ARGS__)
#else
#define SDRIVE_TELEMETRY_WRN(format, ...)
#endif

#if ARCH_CONFIG_VERBOSE >= 1
#define SDRIVE_TELEMETRY_ERR(format, ...) sdrive_telemetry_printf("[ERR %s:%d]" format, __FILE__, __LINE__, ## __VA_ARGS__)
#else
#define SDRIVE_TELEMETRY_ERR(format, ...)
#endif

#endif