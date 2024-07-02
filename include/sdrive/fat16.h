/**
 * @file fat16.h
 * @brief Synch static lib for fat16 driver
 * OS is only meant for 1 FS to be accesed at once (and 1 disk)
 */

#ifndef INCLUDE_SDRIVE_FAT16_H_
#define INCLUDE_SDRIVE_FAT16_H_

/**
 * @brief Grabs FAT table and other things
 * Needs to be ran before any disk operations happen
 */
int sdrive_fat16_init(unsigned lba_bootsector);

/**
 * @brief Closes everything
 */
int sdrive_fat16_fini();

#endif