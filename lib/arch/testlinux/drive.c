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

inline int_fast16_t sdrive_drive_getblocksize() {
    return 512;
}

int_fast8_t sdrive_drive_readblock(void* data, unsigned lba) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    return fread(data, sdrive_drive_getblocksize(), 1, fp);
}

int_fast8_t sdrive_drive_writeblock(void* data, unsigned lba) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    return fwrite(data, sdrive_drive_getblocksize(), 1, fp);
}

int sdrive_drive_readmultiblock(void* data, unsigned lba, size_t num) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    return fread(data, sdrive_drive_getblocksize(), num, fp);
}

int sdrive_drive_writemultiblock(void* data, unsigned lba, size_t num) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    return fwrite(data, sdrive_drive_getblocksize(), num, fp);
}