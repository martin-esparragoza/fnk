/**
 * @file main.c
 * Entry point of the operating system
 */

#include "../include/sdrive/telemetry.h"
#include "../include/sdrive/drive.h"
#include "../include/sdrive/fat16.h"
#include "../lib/util/memdump.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

__attribute__((__used__,section(".memdump"))) struct util_memdump md;

static void errorhang();

int __attribute__((noreturn)) main() {
    if (!(md.telemetry_init_status = sdrive_telemetry_init()))
        SDRIVE_TELEMETRY_INF("Successfully inited static telemetry driver\n");

    // JANK AS HELL FIXME
    md.drive_init_status = sdrive_drive_init();
    for (unsigned char i = 0; i < 3 && md.drive_init_status; i++) {
        SDRIVE_TELEMETRY_WRN("Failed to init drive static driver. Retrying..\n");

        md.drive_init_status = sdrive_drive_init();
    }
    if (md.drive_init_status)
        errorhang();
    
    if ((md.fat16_init_status = sdrive_fat16_init(0)) != SDRIVE_FAT16_ERRC_OK) {
        SDRIVE_TELEMETRY_ERR("Failed to init fat16 static driver. Error: %s\n", sdrive_fat16_errctostr(md.fat16_init_status));
        errorhang();
    }

    struct sdrive_fat16_file* file = __builtin_alloca(sdrive_fat16_file_sizeof());
    int errc = SDRIVE_FAT16_ERRC_OK;
    if ((errc = sdrive_fat16_root_file_open("TESTFILE", file)) != SDRIVE_FAT16_ERRC_OK) {
        SDRIVE_TELEMETRY_ERR("Failed to open file. Error: %s\n", sdrive_fat16_errctostr(errc));
        errorhang();
    }
    
    void* buffer = __builtin_alloca_with_align(sdrive_fat16_getbytespercluster(), 8);
    if ((errc = sdrive_fat16_file_readcluster(file, buffer)) != SDRIVE_FAT16_ERRC_OK) {
        SDRIVE_TELEMETRY_ERR("Error: %s\n", sdrive_fat16_errctostr(errc));
        errorhang();
    }
    
    md.main_return_code =
        sdrive_telemetry_fini() |
        sdrive_drive_fini() |
        sdrive_fat16_fini();

    // Jump out here
}

static void __attribute__((noreturn)) errorhang() {
    SDRIVE_TELEMETRY_ERR("Hanging due to error..\n");
    while (1);
}