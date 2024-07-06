/**
 * @file config.h
 * @brief Config options such as endianness and stack direction
 * It is NOT my job to prevent YOUR mistypes. If you did something stupid deal with it.
 */

#ifndef INCLUDE_ARCH_CONFIG_H_
#define INCLUDE_ARCH_CONFIG_H_

#define ARCH_CONFIG_VERBOSE 3
#define ARCH_CONFIG_STACK_DIR_DOWN ///< Define this to DOWN or UP
// #define ARCH_CONFIG_BIG_ENDIAN ///< Define this to be LITTLE or BIG

#define ARCH_CONFIG_FAT16_SECTORBUFFER_SZ 4 // 4 Sectors
#define ARCH_CONFIG_FAT16_LFNQUEUE_SZ 8 // 64 possible LFN contenders at a time

#endif
