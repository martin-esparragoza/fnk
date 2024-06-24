/**
 * @file telemetry.h
 * @brief Telemetry output (implementation of this can be skipped if desired)
 */

/**
 * @brief Init telemetry before sending anything
 * @return Error code
 */
unsigned char sdrive_telemetry_init();

/**
 * @brief Remove telemetry stream
 */
unsigned char sdrive_telemetry_fini();

/**
 * @brief Put string
 */
unsigned char sdrive_telemetry_puts();

/**
 * @brief Put string to telemetry
 * @return Error code
 */
unsigned char sdrive_telemetry_printf(const char* format, ...);