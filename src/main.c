/**
 * @file main.c
 * Entry point of the operating system
 */

#include "../include/sdrive/telemetry.h"
#include <stdbool.h>

static __attribute__((__used__,section(".memdump"))) struct { ///< Debug information memdump
    unsigned char telemetry_init_status;
    unsigned char drive_init_status;
    int main_return_code
} memdump;

int main() __attribute__((noreturn)) {
    if (!(memdump.telemetry_status = sdrive_telemetry_init()))
        sdrive_telemetry_printf("STATIC DRIVER TELEMETRY INIT SUCCESS\n");

    memdump.drive_init_status = sdrive_drive_init();
    for (unsigned char i = 0; i < 3 && !memdump.drive_init_status; i++) {
        sdrive_telemetry_log("Failed to init drive static driver. Retrying..\n")

        memdump.drive_init_status = sdrive_drive_init();
    }


    main_return_code =
        sdrive_telemetry_fini() |
        sdrive_drive_fini();

    // Jump out here
}