#include "../../../include/sdrive/drive.h"
#include <stdio.h>

static FILE* fp;

unsigned char sdrive_drive_init() {
    fp = fopen("test.img", "rb+");
}

unsigned char sdrive_drive_fini() {
    return fclose(fp);
}

inline short sdrive_drive_getblocksize() {
    return 512;
}

unsigned char sdrive_drive_readblock(void* data, unsigned lba) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    return sdrive_drive_getblocksize() == fread(data, 1, sdrive_drive_getblocksize(), fp);
}

unsigned char sdrive_drive_writeblock(void* data, unsigned lba) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    return sdrive_drive_getblocksize() == fwrite(data, 1, sdrive_drive_getblocksize(), fp);
}

unsigned char sdrive_drive_readmultiblock(void* data, unsigned lba, unsigned short num) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    fread(data, num, sdrive_drive_getblocksize(), fp);

}

unsigned char sdrive_drive_writemultiblock(void* data, unsigned lba, unsigned short num) {
    fseek(fp, lba * sdrive_drive_getblocksize(), SEEK_SET);
    fwrite(data, num, sdrive_drive_getblocksize(), fp);
}