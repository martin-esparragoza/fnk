/**
 * @file fat16.h
 * @brief Synch static lib for fat16 driver
 * OS is only meant for 1 FS to be accesed at once (and 1 disk)
 */

#ifndef INCLUDE_SDRIVE_FAT16_H_
#define INCLUDE_SDRIVE_FAT16_H_

struct sdrive_fat16_file;
typedef struct sdrive_fat16_file sdrive_fat16_file_t;

/**
 * @brief Grabs FAT table and other things
 * Needs to be ran before any disk operations happen
 */
int sdrive_fat16_init(unsigned lba_bootsector);

/**
 * @brief Opens a file
 * @param path String file path. ABSOLUTE PATHING IS A MUST. Start with /
 * @param fp NULL if can't open file
 */
void sdrive_fat16_fopen(const char* path, struct sdrive_fat16_file* fp);

/**
 * @brief Closes everything
 */
int sdrive_fat16_fini();

#endif