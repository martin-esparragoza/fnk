/**
 * @file main.c
 * Entry point of the operating system
*/

#include "include/sdrive/telemetry.h"
#include "include/sdrive/drive.h"
#include "include/sdrive/fat16.h"
#include "lib/util/memdump.h"
#include "include/mem/alloc.h"
#include "attr.h"
#include "types.h"

COMP_ATTR__USED__ COMP_ATTR__SECTION__(".memdump") struct util_memdump md;
int errc = 0; // 0 Isnt standardized or anything but whatever
              // This is a reused errc variable

void COMP_ATTR__NORETURN__ errorhang() {
    SDRIVE_TELEMETRY_ERR("Hanging due to error..\n");
    while (1);
}

int COMP_ATTR__NORETURN__ main() {
    if (!(md.telemetry_init_status = sdrive_telemetry_init()))
        SDRIVE_TELEMETRY_INF("Successfully inited static telemetry driver\n");
    else
        SDRIVE_TELEMETRY_WRN("Failed to init static telemetry driver\n");
    
    mem_alloc_init(2);
    SDRIVE_TELEMETRY_INF("Inited memory utils\n");
    
    // JANK AS HELL FIXME
    md.drive_init_status = sdrive_drive_init();
    for (unsigned char i = 0; i < 3 && md.drive_init_status; i++) {
        SDRIVE_TELEMETRY_WRN("Failed to init drive static driver. Retrying..\n");

        md.drive_init_status = sdrive_drive_init();
    }

    if (md.drive_init_status)
        errorhang();
    
    if ((md.fat16_init_status = sdrive_fat16_init(0)) > SDRIVE_FAT16_ERRC_OK) {
        SDRIVE_TELEMETRY_ERR("Failed to init fat16 static driver. Error: %s\n", sdrive_fat16_errctostr(md.fat16_init_status));
        errorhang();
    }
    
    void* buf3 = mem_alloc_malloc(10);
    void* buf4 = mem_alloc_malloc(10);
    void* buf = mem_alloc_malloc(10);
    mem_alloc_free(buf);
    void* buf2 = mem_alloc_malloc(20);
    mem_alloc_free(buf2);
    mem_alloc_free(buf3);
    mem_alloc_free(buf4);
    buf = mem_alloc_malloc(1023);
    mem_alloc_malloc(100);
    
    /*SDRIVE_TELEMETRY_INF("Searching root directory for directory TESTDIR\n");
    struct sdrive_fat16_dir* dir1 = __builtin_alloca(sdrive_fat16_dir_sizeof());
    if ((errc = sdrive_fat16_root_dir_open("TESTDIR", dir1)) > SDRIVE_FAT16_ERRC_OK) {
        SDRIVE_TELEMETRY_ERR("Failed to open dir. Error: %s\n", sdrive_fat16_errctostr(errc));
        errorhang();
    }

    SDRIVE_TELEMETRY_INF("Searching TESTDIR for directory INTERNALDIR\n");
    struct sdrive_fat16_dir* dir2 = __builtin_alloca(sdrive_fat16_dir_sizeof());
    if ((errc = sdrive_fat16_dir_open("INTERNALDIR", dir1, dir2)) > SDRIVE_FAT16_ERRC_OK) {
        SDRIVE_TELEMETRY_ERR("Failed to open directory. Error: %s\n", sdrive_fat16_errctostr(errc));
        errorhang();
    }

    SDRIVE_TELEMETRY_INF("Searching INTERNALDIR for file TESTFILE\n");
    struct sdrive_fat16_file* file = __builtin_alloca(sdrive_fat16_dir_sizeof());
    if ((errc = sdrive_fat16_file_open("TESTFILE", dir2, file)) > SDRIVE_FAT16_ERRC_OK) {
        SDRIVE_TELEMETRY_ERR("Failed to open file. Error: %s\n", sdrive_fat16_errctostr(errc));
        errorhang();
    }

    SDRIVE_TELEMETRY_INF("Reading TESTFILE cluster by cluster\n");
    void* buffer = __builtin_alloca_with_align(sdrive_fat16_getbytespercluster(), 8);
    for (unsigned i = 0; i < 5; i++) {
    if ((errc = sdrive_fat16_file_readcluster(file, buffer)) > SDRIVE_FAT16_ERRC_OK) {
        SDRIVE_TELEMETRY_ERR("Failed to read file. Error: %s\n", sdrive_fat16_errctostr(errc));
        errorhang();
    }
    SDRIVE_TELEMETRY_INF("%s\n", buffer);
    } */
    
// This really doesn't give information other than the fact that something bad happened
    md.main_return_code = !!(
        sdrive_telemetry_fini() |
        sdrive_drive_fini() |
        sdrive_fat16_fini()
    );

    // Jump out here
}