/**
 * @file fat16.h
 * @brief Synch static lib for fat16 driver
 * OS is only meant for 1 FS to be accesed at once (and 1 disk)
 */

#ifndef INCLUDE_SDRIVE_FAT16_H_
#define INCLUDE_SDRIVE_FAT16_H_

#include <stdint.h>

#define SDRIVE_FAT16_ERRC_OK 0
#define SDRIVE_FAT16_ERRC_CORRUPTBS 1
#define SDRIVE_FAT16_ERRC_READ_FAIL 2
#define SDRIVE_FAT16_ERRC_FILE_NOT_FOUND 3

struct sdrive_fat16_file;
typedef struct sdrive_fat16_file sdrive_fat16_file_t;

/**
 * @brief Convert errc to string
 *
 * @param errc Error code
 * @return String and if cannot find returns NULL
 */
const char* sdrive_fat16_errctostr(int errc);

/**
 * @brief Grabs FAT table and other things
 * Needs to be ran before any disk operations happen
 */
int sdrive_fat16_init(unsigned lba_bootsector);

/**
 * @brief Opens a file
 * @param path String file path. ABSOLUTE PATHING IS A MUST (omit the starting slash which indicates the root directory e.g. /home/code would become home/code). NULL terminated ofc
 * @param fp NULL if can't open file
 *
 * @return error code
 */
int sdrive_fat16_fopen(const char* path, struct sdrive_fat16_file* fp);

/**
 * @brief Closes everything
 */
int sdrive_fat16_fini();

#endif