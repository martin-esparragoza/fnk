/**
 * @file fat16.h
 * @brief Synch static lib for fat16 driver
 * OS is only meant for 1 FS to be accesed at once (and 1 disk)
 * Partitioning unsupported
 */

#ifndef INCLUDE_SDRIVE_FAT16_H_
#define INCLUDE_SDRIVE_FAT16_H_

#include <stdint.h>

#define SDRIVE_FAT16_ERRC_OK 0
#define SDRIVE_FAT16_ERRC_CORRUPTBS 1
#define SDRIVE_FAT16_ERRC_READ_FAIL 2
#define SDRIVE_FAT16_ERRC_FILE_NOT_FOUND 3
#define SDRIVE_FAT16_ERRC_INVALID_PATH 4
#define SDRIVE_FAT16_ERRC_FATSZ_TOO_SMALL 5
#define SDRIVE_FAT16_ERRC_CORRUPTED_FILE 6
#define SDRIVE_FAT16_ERRC_EOF 7

/**
 * @private
 */
typedef struct sdrive_fat16_file {
    uint_fast16_t startingcluster;
    uint_fast16_t nextcluster;
    uint_fast16_t size; //< Clusters
    uint_fast16_t clustersread;
} sdrive_fat16_file_t;

/**
 * @private
 */
typedef struct sdrive_fat16_dir {
    //struct sdrive_fat16_file fp;
} sdrive_fat16_dir_t;

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

struct sdrive_fat16_root* sdrive_fat16_getroot();

/**
 * @brief Opens a directory
 * @param path String file name
 * @param fp Pointer to directory
 *
 * @return error code
 */
int sdrive_fat16_root_dopen(const char* file, struct sdrive_fat16_dir* fp);

int sdrive_fat16_root_fopen(const char* file, struct sdrive_fat16_file* fp);

int sdrive_fat16_fopen(const char* file, struct sdrive_fat16_dir* dp, struct sdrive_fat16_file* fp);

int sdrive_fat16_freadcluster(struct sdrive_fat16_file* fp, void* buffer);

uint_fast32_t sdrive_fat16_getbytespercluster();

/**
 * @brief Closes everything
 */
int sdrive_fat16_fini();

#endif