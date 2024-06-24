/**
 * @file fat16.h
 * @brief Synch static lib for fat16 driver
 * OS is only meant for 1 FS to be accesed at once (and 1 disk)
 */

/**
 * @brief Grabs FAT table and other things
 * Needs to be ran before any disk operations happen
 */
unsigned char sdrive_fat16_init();