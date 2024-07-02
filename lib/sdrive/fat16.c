#include "../../include/sdrive/fat16.h"
#include "../../include/sdrive/drive.h"
#include "../../include/sdrive/telemetry.h"
#include "../../include/arch/config.h"
#include "../util/memdump.h"
#include <stdint.h>
#include <stdbool.h>

extern struct memdump md;

static bool ispowertwo(unsigned x);
static inline bool ispowertwo(unsigned x) {
    return x && !(x & (x - 1)); // && x to make sure x != 0
}

// Do note that you can treat this as a union to bring fat32 support
struct __attribute__((packed)) {
    uint8_t jmpboot[3];
    uint8_t oemname[8];
    uint16_t bytespersector;
    uint8_t bytespercluster;
    uint16_t reservedsectors;
    uint8_t numfats;
    uint16_t rootentrycount;
    uint16_t totalsectors16;
    uint8_t mediatype;
    uint16_t fatsize16;
    uint16_t sectorspertrack;
    uint16_t numheads;
    uint32_t hiddensectors;
    uint32_t totalsectors32;
    uint8_t drivenum;
    uint8_t reserved; // Unused
    uint8_t extendedsignature;
    uint32_t id;
    uint8_t label[11];
    uint8_t strfattype[8];
    uint8_t bootcode[448];
    uint16_t signature;
}* bs;


int sdrive_fat16_init(unsigned lba_bootsector) {
    uint_fast16_t blocksize = sdrive_drive_getblocksize();
    bs = __builtin_alloca_with_align(blocksize, 8);
    if ((md.num_blocks_read_bs = sdrive_drive_readblock(bs, lba_bootsector)) != 1)
        return -1;
    
    SDRIVE_TELEMETRY_INF("oemname: %.8s\n", bs->oemname);
    SDRIVE_TELEMETRY_INF("Bytes/Sector: %hu\n", bs->bytespersector);
    SDRIVE_TELEMETRY_INF("Bytes/Cluster: %hu\n", bs->bytespercluster);
    SDRIVE_TELEMETRY_INF("Reserved Sectors: %hhu\n", bs->reservedsectors);
    SDRIVE_TELEMETRY_INF("# of FATs: %hhu\n", bs->numfats);
    SDRIVE_TELEMETRY_INF("Root Entry Count: %hu\n", bs->rootentrycount);
    SDRIVE_TELEMETRY_INF("Total Sectors (16 bit): %hu\n", bs->totalsectors16);
    SDRIVE_TELEMETRY_INF("Media Type: 0x%02hhX\n", bs->mediatype);
    SDRIVE_TELEMETRY_INF("FAT size: %hu\n", bs->fatsize16);
    SDRIVE_TELEMETRY_INF("Sectors/Track: %hu\n", bs->sectorspertrack);
    SDRIVE_TELEMETRY_INF("# Of Disk Heads: %hu\n", bs->numheads);
    SDRIVE_TELEMETRY_INF("Hidden Sectors: %u\n", bs->hiddensectors);
    SDRIVE_TELEMETRY_INF("Total Sectors (32 bit): %u\n", bs->totalsectors32);
    SDRIVE_TELEMETRY_INF("Drive # (BIOS + IBM PC): 0x%02hhX\n", bs->drivenum);
    SDRIVE_TELEMETRY_INF("ExSig: %hhu\n", bs->extendedsignature);
    SDRIVE_TELEMETRY_INF("ID: %u\n", bs->id);
    SDRIVE_TELEMETRY_INF("Label: %.11s\n", bs->label);
    SDRIVE_TELEMETRY_INF("Fat Type (unreliable): %.8s\n", bs->strfattype);
    SDRIVE_TELEMETRY_INF("0x55AA Existance: 0x%04hX\n", bs->signature);

    // Ugly bootsector verification

    bool flag = false;
    if ((flag |= (!ispowertwo(bs->bytespersector) || bs->bytespersector >= 4096)))
        SDRIVE_TELEMETRY_ERR("Bytes/Sector is not 512, 1024, 2048, or 4096\n");
    if ((flag |= (!ispowertwo(bs->bytespercluster) || bs->bytespercluster >= 128)))
        SDRIVE_TELEMETRY_ERR("Bytes/Cluster is not a power of two greater than 0 between 1-128\n");
    if ((flag |= (bs->reservedsectors == 0)))
        SDRIVE_TELEMETRY_ERR("Reserved sectors must not be 0 for FAT16\n");
    if ((flag |= !(bs->numfats == 1 || bs->numfats == 2)))
        SDRIVE_TELEMETRY_ERR("# of FATs must be 1 or 2\n");
    if ((flag |= (((bs->rootentrycount * 32) % bs->bytespersector) != 0)))
        SDRIVE_TELEMETRY_ERR("Root entry count when multiplied by 32 must be an even multiple of Bytes/Sector\n");
    if ((flag |= !(bs->mediatype == 0xF0 || (bs->mediatype >= 0xF8 && bs->mediatype <= 0xFF))))
        SDRIVE_TELEMETRY_ERR("Media type is not 0xF0, 0xF8, 0xF9, 0xFA, 0xFC, 0xFD, 0xFE, or 0xFF\n");

    if (flag)
        return -1;

    return 0;
}

int sdrive_fat16_fini() {
    return 0;
}