#include "../../../include/sdrive/fat16.h"
#include "../../../include/sdrive/drive.h"
#include <stdint.h>

typedef struct __attribute__((packed)) sdrive_fat16_sectorzero {
    uint8_t jmpboot[3];
} sdrive_fat16_sectorzero_t;

int sdrive_fat16_init() {
    uint8_t sector[sdrive_drive_getblocksize()];
    return 0;
}

int sdrive_fat16_fini() {
    return 0;
}