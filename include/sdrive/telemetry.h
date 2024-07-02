/**
 * @file telemetry.h
 * @brief Telemetry output (implementation of this can be skipped if desired)
 */

#ifndef INCLUDE_SDRIVE_TELEMETRY_H_
#define INCLUDE_SDRIVE_TELEMETRY_H_

/**
 * @brief Init telemetry before sending anything
 * @return Error code
 */
int sdrive_telemetry_init();

/**
 * @brief Remove telemetry stream
 */
int  sdrive_telemetry_fini();

/**
 * @brief Put string
 */
int  sdrive_telemetry_puts();

/**
 * @brief Put string to telemetry
 * @return Error code
 */
int sdrive_telemetry_printf(const char* format, ...);

#define SDRIVE_TELEMETRY_LOG(format, ...) sdrive_telemetry_printf("[%s:%d]" format, __FILE__, __LINE__, ## __VA_ARGS__)

#endif