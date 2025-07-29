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
    unsigned telemetry_init_errc;
    unsigned vfs_init_errc;
    unsigned errcsum;
};

#endif