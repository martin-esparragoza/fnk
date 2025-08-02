#ifndef COMMON_INCLUDE_PJD_H_
#define COMMON_INCLUDE_PJD_H_

#include "common/include/fnkconfig.h"
#include "types.h"
#include "attr.h"

typedef struct COMMON_ATTR__PACKED__ common_pjd {
    char name[COMMON_FNKCONFIG_NAMELEN];
    uintptr_t functions[COMMON_FNKCONFIG_MAX_LIBFUNCTIONS];
} common_pjd_t;

#endif