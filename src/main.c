/**
 * @file main.c
 * Entry point of the bootloder code
*/

#include "include/sdrive/telemetry.h"
#include "lib/util/memdump.h"
#include "include/mem/alloc.h"
#include "attr.h"
#include "types.h"

COMP_ATTR__USED__ COMP_ATTR__SECTION__(".memdump") struct util_memdump md;
static int errc = 0; // 0 Isnt standardized or anything but whatever
              // This is a reused errc variable

void COMP_ATTR__NORETURN__ errorhang() {
    SDRIVE_TELEMETRY_ERR("Hanging due to error..\n");
    while (1);
}

int COMP_ATTR__NORETURN__ main() {
    mem_alloc_init(3);

    errorhang();
}