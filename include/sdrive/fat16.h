/**
 * @file fat16.h
 * @brief Synch static lib for fat16 driver
 * OS is only meant for 1 FS to be accesed at once (and 1 disk)
 * Partitioning unsupported
 */

#ifndef INCLUDE_SDRIVE_FAT16_H_
#define INCLUDE_SDRIVE_FAT16_H_

#include <stdint.h>
#include <stddef.h>

#define SDRIVE_FAT16_ERRC_OK 0
#define SDRIVE_FAT16_ERRC_CORRUPTBS 1
#define SDRIVE_FAT16_ERRC_READ_FAIL 2
#define SDRIVE_FAT16_ERRC_FILE_NOT_FOUND 3
#define SDRIVE_FAT16_ERRC_INVALID_PATH 4
#define SDRIVE_FAT16_ERRC_FATSZ_TOO_SMALL 5
#define SDRIVE_FAT16_ERRC_CORRUPTED_FILE 6
#define SDRIVE_FAT16_ERRC_EOF 7
#define SDRIVE_FAT16_ERRC_NOT_A_FILE 8
#define SDRIVE_FAT16_ERRC_NOT_A_DIR 9
#define SDRIVE_FAT16_ERRC_EOD 10

struct sdrive_fat16_file;
typedef struct sdrive_fat16_file sdrive_fat16_file_t;
struct sdrive_fat16_dir;
typedef struct sdrive_fat16_dir sdrive_fat16_dir_t;

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
 * @brief Opens a directory from /
 * @param file String file name
 * @param fp Pointer to directory to create
 *
 * @return error code
 */
int sdrive_fat16_root_dir_open(const char* file, struct sdrive_fat16_dir* fp);

/**
 * @brief Opens a file from /
 * @param file String file name
 * @param fp Pointer to file to create
 *
 * @return error code
 */
int sdrive_fat16_root_file_open(const char* file, struct sdrive_fat16_file* fp);

/**
 * @brief Opens a file from a directory
 * @param file String file name
 * @param dp Pointer to directory
 * @param fp Pointer to file
 *
 * @return error code
 */
int sdrive_fat16_file_open(const char* file, struct sdrive_fat16_dir* dp, struct sdrive_fat16_file* fp);

/**
 * @brief Opens a directory from a directory
 * @param file String directory name
 * @param dp Pointer to directory
 * @param fp Pointer to file
 */
int sdrive_fat16_dir_open(const char* file, struct sdrive_fat16_dir* dp, struct sdrive_fat16_dir* dpout);

/**
 * @brief Reads a cluster from a file
 *
 * @param fp File to read from
 * @param buffer Output buffer
 */
int sdrive_fat16_file_readcluster(struct sdrive_fat16_file* fp, void* buffer);

/**
 * @brief Use this to create the readcluster buffer
 */
uint_fast32_t sdrive_fat16_getbytespercluster();

/**
 * Sizeof operator for allocation
 */
size_t sdrive_fat16_file_sizeof();

/**
 * Sizeof operator for allocation
 */
size_t sdrive_fat16_dir_sizeof();

/**
 * @brief Closes everything
 */
int sdrive_fat16_fini();

#endif