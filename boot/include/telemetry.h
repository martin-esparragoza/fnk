/**
 * @file telemetry.h
 * @brief Static telemetry driver. You can just not implement this as well and things will go fine
 */

#ifndef BOOT_INCLUDE_TELEMETRY_H_
#define BOOT_INCLUDE_TELEMETRY_H_

#include "common/include/config.h"

/**
 * @brief Init telemetry before sending anything
 * @retval 0 on OK
 * @return Error code
 *
 * If this fails the code should still be able to run
 */
unsigned boot_telemetry_init(void);

/**
 * @brief Remove telemetry stream
 * @retval 0 on OK
 * @return Error code
 */
unsigned boot_telemetry_fini(void);

/**
 * @brief Put string
 * @note Should do nothing if failed telemetry initialization
 * @retval 0 on OK
 * @return Error code
 */
unsigned boot_telemetry_puts(const char* str);

/**
 * @brief Put character
 * @note Should do nothing if failed telemetry initialization
 * @retval 0 on OK
 * @return Error code
 */
unsigned boot_telemetry_putc(char c);

/**
 * @brief Put string to telemetry with printf things
 * @note Should do nothing if failed telemetry initialization
 * @retval 0 on OK
 * @return Error code
 */
unsigned boot_telemetry_printf(const char* format, ...);

#define BOOT_TELEMETRY_LOG(format, ...) boot_telemetry_printf("[%s:%d]" format, __FILE__, __LINE__, ## __VA_ARGS__)

#if COMMON_CONFIG_VERBOSE_LEVEL >= 3
#define BOOT_TELEMETRY_INF(format, ...) boot_telemetry_printf("[INF %s:%d]" format, __FILE__, __LINE__, ## __VA_ARGS__)
#else
#define BOOT_TELEMETRY_INF(format, ...)
#endif

#if COMMON_CONFIG_VERBOSE_LEVEL >= 2
#define BOOT_TELEMETRY_WRN(format, ...) boot_telemetry_printf("[WRN %s:%d]" format, __FILE__, __LINE__, ## __VA_ARGS__)
#else
#define BOOT_TELEMETRY_WRN(format, ...)
#endif

#if COMMON_CONFIG_VERBOSE_LEVEL >= 1
#define BOOT_TELEMETRY_ERR(format, ...) boot_telemetry_printf("[ERR %s:%d]" format, __FILE__, __LINE__, ## __VA_ARGS__)
#else
#define BOOT_TELEMETRY_ERR(format, ...)
#endif

#endif