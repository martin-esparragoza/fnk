/**
 * @file main.c
 * Entry point of the operating system
 */

#include "../include/sdrive/telemetry.h"
#include "../include/sdrive/drive.h"
#include "../include/sdrive/fat16.h"
#include <stdint.h>
#include <stdbool.h>

static __attribute__((__used__,section(".memdump"))) struct { ///< Debug information memdump
    unsigned char telemetry_init_status;
    unsigned char drive_init_status;
    unsigned char fat16_init_status;
    int main_return_code;
} memdump;

static void errorhang();

int __attribute__((noreturn)) main() {
    if (!(memdump.telemetry_init_status = sdrive_telemetry_init()))
        SDRIVE_TELEMETRY_LOG("Successfully inited static telemetry driver\n");

    memdump.drive_init_status = sdrive_drive_init();
    for (unsigned char i = 0; i < 3 && !memdump.drive_init_status; i++) {
        SDRIVE_TELEMETRY_LOG("Failed to init drive static driver. Retrying..\n");

        memdump.drive_init_status = sdrive_drive_init();
    }
    
    if ((memdump.fat16_init_status = sdrive_fat16_init())) {
        SDRIVE_TELEMETRY_LOG("Failed to init fat16 static driver\n");
        errorhang();
    }

    memdump.main_return_code =
        sdrive_telemetry_fini() |
        sdrive_drive_fini() |
        sdrive_fat16_fini();

    // Jump out here
}

static void __attribute__((noreturn)) errorhang() {
    SDRIVE_TELEMETRY_LOG("Hanging due to error..\n");
    while (1);
}