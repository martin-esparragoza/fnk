// What entry should jump to. Main bootloader code

#include "boot/include/telemetry.h"
#include "boot/include/memdump.h"
#include "attr.h"
#include "types.h"

COMP_ATTR__USED__ COMP_ATTR__SECTION__(".memdump") struct boot_memdump md;
static int errc = 0; // 0 Isnt standardized or anything but whatever
              // This is a reused errc variable

void COMP_ATTR__NORETURN__ errorhang() {
    BOOT_TELEMETRY_ERR("Hanging due to error..\n");
    while (1);
}

int COMP_ATTR__NORETURN__ main() {
    errorhang();
}