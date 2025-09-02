#include "boot/include/vfs.h"
#include "boot/lib/vfs.h"
#include "common/include/config.h"
#include "common/include/errc.h"

static const char* errcstr_def[] = {
    [BOOT_VFS_ERRC_DIR_NOT_FOUND - COMMON_ERRC_BASE] = "Directory not found on attempted open",
    [BOOT_VFS_ERRC_DIR_FAILED_CLOSE - COMMON_ERRC_BASE] = "Failed to close directory",
    [BOOT_VFS_ERRC_DIR_NO_NEXT - COMMON_ERRC_BASE] = "Failed to get next file in directory",
    [BOOT_VFS_ERRC_FILE_NOT_FOUND - COMMON_ERRC_BASE] = "File not found on attempted open",
    [BOOT_VFS_ERRC_FILE_FAILED_CLOSE - COMMON_ERRC_BASE] = "Failed to close file"
};

const char* boot_vfs_errctostr(unsigned errc) {
    if (errc >= COMMON_ERRC_BASE) {
        unsigned i = errc - COMMON_ERRC_BASE;
        if (i < (sizeof(errcstr_def) / sizeof(errcstr_def[0])))
            return errcstr_def[i];
        return boot_vfs_errctostr_alt(errc);
    }
    return "Ok";
}

const char* boot_vfs_errctostr_alt(unsigned errc) {
    errc -= BOOT_VFS_ERRC_DEF_BASE;
    if (errc < boot_vfs_errcstr_alt_sizeof)
        return boot_vfs_errcstr_alt[errc];
    return NULL;
}