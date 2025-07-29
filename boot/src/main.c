// What entry should jump to. Main bootloader code

#include "boot/include/telemetry.h"
#include "boot/include/memdump.h"
#include "boot/include/vfs.h"
#include "attr.h"
#include "builtin.h"

COMP_ATTR__USED__ COMP_ATTR__SECTION__(".memdump") struct boot_memdump md;

void COMP_ATTR__NORETURN__ errorhang(void) {
    BOOT_TELEMETRY_ERR("Hanging due to error..\n");
    while (1);
}

void error_and_sum(unsigned errc, const char* (*errctostr)(unsigned)) {
    md.errcsum += errc;
    if (md.errcsum) {
        BOOT_TELEMETRY_ERR("%s\n", errctostr(errc));
        errorhang();
    }
}

int COMP_ATTR__NORETURN__ main(void) {
    md.telemetry_init_errc = boot_telemetry_init();
    // Hell am I gonna do? Warn if it goes wrong???

    md.vfs_init_errc = boot_vfs_init();
    md.errcsum += md.vfs_init_errc;
    error_and_sum(md.vfs_init_errc, &boot_vfs_errctostr);

    // TODO: Lib loading
}