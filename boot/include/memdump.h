/**
 * @file memdump.h
 * @brief Memdump that you can see on error. Discarded after boot sequence
 */

#ifndef BOOT_INCLUDE_MEMDUMP_H_
#define BOOT_INCLUDE_MEMDUMP_H_

#include "attr.h"

/**
 * @brief Just something a person can grab if something went wrong
 */
struct COMP_ATTR__PACKED__ boot_memdump { ///< Debug information memdump
    unsigned char telemetry_init_status;
    unsigned char mem_init_status;
    unsigned char drive_init_status;
    unsigned char fat16_init_status;
    int main_return_code;
    int num_blocks_read_bs; ///< # Of blocks read when attempting to read bootsector (errc should be 1)
};

#endif