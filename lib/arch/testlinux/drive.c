#include "../../../include/sdrive/drive.h"
#include <stdio.h>
#include <stdint.h>

static FILE* fp;

int sdrive_drive_init() {
    fp = fopen("test.img", "a");
    fclose(fp);
    fp = fopen("test.img", "rb+");
    return 0;
}

int sdrive_drive_fini() {
    return fclose(fp);
}

inline uint_fast16_t sdrive_drive_getblocksize() {
    return 512;
}

int sdrive_drive_readblock(void* data, unsigned lba) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    return sdrive_drive_getblocksize() == fread(data, 1, sdrive_drive_getblocksize(), fp);
}

int sdrive_drive_writeblock(void* data, unsigned lba) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    return sdrive_drive_getblocksize() == fwrite(data, 1, sdrive_drive_getblocksize(), fp);
}

int_fast16_t sdrive_drive_readmultiblock(void* data, unsigned lba, uint_fast16_t num) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    return fread(data, num, sdrive_drive_getblocksize(), fp);
}

int_fast16_t sdrive_drive_writemultiblock(void* data, unsigned lba, uint_fast16_t num) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    return fwrite(data, num, sdrive_drive_getblocksize(), fp);
}