/**
 * @file config.h
 * @brief Config options such as endianness and stack direction
 * It is NOT my job to prevent YOUR mistypes. If you did something stupid deal with it.
 */

#ifndef INCLUDE_ARCH_CONFIG_H_
#define INCLUDE_ARCH_CONFIG_H_

#define ARCH_CONFIG_VERBOSE 3
#define ARCH_CONFIG_STACK_DIR_DOWN ///< Define this to down or don't to make it up
// #define ARCH_CONFIG_BIG_ENDIAN ///< Define this to big or dont to make it little

#define ARCH_CONFIG_FAT16_SECTORBUFFER_SZ 4 // 4 Sectors
#define ARCH_CONFIG_FAT16_FAT 0 //< FAT number to use
// #define ARCH_CONFIG_FAT16_OVERWRITE_FATS ///< Define this in order to update all other FATs whenever a FAT write occurs
#define ARCH_CONFIG_FAT16_FATSZ 32768 ///< Size of buffer allocated (in bytes). If you want to be safe for any volume use 256KB

#endif
