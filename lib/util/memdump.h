#ifndef LIB_UTIL_MEMDUMP_H_
#define LIB_UTIL_MEMDUMP_H_

#include "attr.h"

struct INCLUDE_COMP_ATTR_PACKED util_memdump { ///< Debug information memdump
    unsigned char telemetry_init_status;
    unsigned char drive_init_status;
    unsigned char fat16_init_status;
    int main_return_code;
    int num_blocks_read_bs; ///< # Of blocks read when attempting to read bootsector (errc should be 1)
};

#endif