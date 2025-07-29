#include "boot/include/vfs.h"
#include "boot/lib/vfs.h"

static const char* errcstr_def[] = {
    [BOOT_VFS_ERRC_OK] = "Ok",
    [BOOT_VFS_ERRC_DIR_NOT_FOUND] = "Directory not found on attempted open",
    [BOOT_VFS_ERRC_DIR_FAILED_CLOSE] = "Failed to close directory",
    [BOOT_VFS_ERRC_DIR_NO_NEXT] = "Failed to get next file in directory",
    [BOOT_VFS_ERRC_FILE_NOT_FOUND] = "File not found on attempted open",
    [BOOT_VFS_ERRC_FILE_FAILED_CLOSE] = "Failed to close file"
};

const char* boot_vfs_errctostr(int errc) {
    if (errc >= 0) {
        if (errc < sizeof(errcstr_def) / sizeof(errcstr_def[0]) && errc >= 0)
            return errcstr_def[errc];
        return boot_vfs_errctostr_alt(errc);
    }
    return NULL;
}

const char* boot_vfs_errctostr_alt(int errc) {
    errc -= BOOT_VFS_ERRC_DEF_END;
    if (errc < boot_vfs_errcstr_alt_sizeof && errc >= 0)
        return boot_vfs_errcstr_alt[errc];
    return NULL;
}