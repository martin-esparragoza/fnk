#include "../../include/sdrive/fat16.h"
#include "../../include/sdrive/drive.h"
#include "../../include/sdrive/telemetry.h"
#include "../../include/arch/config.h"
#include "../util/memdump.h"
#include "../util/ops.h"
#include <stdint.h>

extern struct util_memdump md;

// Do note that you can treat this as a union to bring fat32 support
struct __attribute__((packed)) {
    uint8_t jmpboot[3];
    uint8_t oemname[8];
    uint16_t bytespersector;
    uint8_t sectorspercluster;
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

typedef struct __attribute__((packed)) sdrive_fat16_dir {
    uint8_t name[11];
    uint8_t attr;
    uint8_t ntres;
    uint8_t createtimetenth;
    uint16_t createtime;
    uint16_t createdate;
    uint16_t accessdate;
    uint16_t firstclusterhi;
    uint16_t writetime;
    uint16_t writedate;
    uint16_t firstclusterlo;
    uint32_t filesize;
} sdrive_fat16_dir_t;

static uint_fast32_t fatstart, fatsize, rootstart, rootsize, datastart, datasize, numclusters;

// Because this driver is literally only going to read only, I'm not going to update the last access dates and also not going to include even a pointer to the directory entry
struct sdrive_fat16_file {
    uint_fast16_t startingcluster;
    uint_fast16_t currentcluster;
};

int sdrive_fat16_init(unsigned lba_bootsector) {
    uint_fast16_t blocksize = sdrive_drive_getblocksize();
    bs = __builtin_alloca_with_align(blocksize, 8);
    if ((md.num_blocks_read_bs = sdrive_drive_readblock(bs, lba_bootsector)) != 1)
        return -1;

    // Painful endian conversion...
#ifdef ARCH_CONFIG_BIG_ENDIAN
    util_ops_bswap(bs->jmpboot, sizeof(bs->jmpboot));
    util_ops_bswap(bs->oemname, sizeof(bs->oemname));
    bs->bytespersector = __builtin_bswap16(bs->bytespersector);
    bs->reservedsectors = __builtin_bswap16(bs->reservedsectors);
    bs->rootentrycount = __builtin_bswap16(bs->rootentrycount);
    bs->totalsectors16 = __builtin_bswap16(bs->totalsectors16);
    bs->fatsize16 = __builtin_bswap16(bs->fatsize16);
    bs->sectorspertrack = __builtin_bswap16(bs->sectorspertrack);
    bs->numheads = __builtin_bswap16(bs->numheads);
    bs->hiddensectors = __builtin_bswap32(bs->hiddensectors);
    bs->totalsectors32 = __builtin_bswap32(bs->totalsectors32);
    bs->id = __builtin_bswap32(bs->id);
    util_ops_bswap(bs->label, sizeof(bs->label));
    util_ops_bswap(bs->strfattype, sizeof(bs->strfattype));
    // Boot code is boot code. It doesn't need to be interprited by us and its endianness should be the systems
    bs->signature = __builtin_bswap16(bs->signature);
#endif

    // Param setting
    fatstart = bs->reservedsectors;
    fatsize = bs->fatsize16 * bs->numfats;
    rootstart = fatstart + fatsize;
    rootsize = (32 * bs->rootentrycount + bs->bytespersector - 1) / bs->bytespersector;
    datastart = rootstart + rootsize;
    datasize = (bs->totalsectors16 == 0 ? bs->totalsectors32 : bs->totalsectors16) - datastart; // Assume that its at least done correctly...
    numclusters = datasize / bs->sectorspercluster;

    SDRIVE_TELEMETRY_INF("OEMName: %.8s\n", bs->oemname);
    SDRIVE_TELEMETRY_INF("Bytes/Sector: %hu\n", bs->bytespersector);
    SDRIVE_TELEMETRY_INF("Sectors/Cluster: %hu\n", bs->sectorspercluster);
    SDRIVE_TELEMETRY_INF("Reserved Sectors: %hhu\n", bs->reservedsectors);
    SDRIVE_TELEMETRY_INF("# of FATs: %hhu\n", bs->numfats);
    SDRIVE_TELEMETRY_INF("Root Entry Count: %hu\n", bs->rootentrycount);
    SDRIVE_TELEMETRY_INF("Total Sectors (16 bit): %hu\n", bs->totalsectors16);
    SDRIVE_TELEMETRY_INF("Media Type: 0x%02hhX\n", bs->mediatype);
    SDRIVE_TELEMETRY_INF("FAT size (sectors): %hu\n", bs->fatsize16);
    SDRIVE_TELEMETRY_INF("Sectors/Track: %hu\n", bs->sectorspertrack);
    SDRIVE_TELEMETRY_INF("# Of Disk Heads: %hu\n", bs->numheads);
    SDRIVE_TELEMETRY_INF("Hidden Sectors: %u\n", bs->hiddensectors);
    SDRIVE_TELEMETRY_INF("Total Sectors (32 bit): %u\n", bs->totalsectors32);
    SDRIVE_TELEMETRY_INF("Drive # (BIOS + IBM PC): 0x%02hhX\n", bs->drivenum);
    SDRIVE_TELEMETRY_INF("ExSig: %hhu\n", bs->extendedsignature);
    if (bs->extendedsignature == 0x29 || bs->extendedsignature == 0x28) { // 3 values are not garbage
        SDRIVE_TELEMETRY_INF("ID: %u\n", bs->id);
        SDRIVE_TELEMETRY_INF("Label: %.11s\n", bs->label);
        SDRIVE_TELEMETRY_INF("Fat Type (unreliable): %.8s\n", bs->strfattype);
    }
    SDRIVE_TELEMETRY_INF("0x55AA Existance: 0x%04hX\n", bs->signature);
    SDRIVE_TELEMETRY_INF("FAT Start: %d\n", fatstart);
    SDRIVE_TELEMETRY_INF("FAT Size (sectors): %d\n", fatsize);
    SDRIVE_TELEMETRY_INF("Root Directory start: %d\n", rootstart);
    SDRIVE_TELEMETRY_INF("Root Directory size (sectors): %d\n", rootsize);
    SDRIVE_TELEMETRY_INF("Data Start: %d\n", datastart);
    SDRIVE_TELEMETRY_INF("Data Size (sectors): %d\n", datasize);
    SDRIVE_TELEMETRY_INF("# of Clusters: %d\n", numclusters);

    // Ugly bootsector verification

    bool flag = false;
    if ((flag |= !(numclusters >= 4086 && numclusters <= 65525)))
        SDRIVE_TELEMETRY_ERR("Numclusters is not between 4086 and 65525 therefore not FAT16 formatted volume\n");
    if ((flag |= (!util_ops_ispowertwo(bs->bytespersector) || bs->bytespersector >= 4096)))
        SDRIVE_TELEMETRY_ERR("Bytes/Sector is not 512, 1024, 2048, or 4096\n");
    if ((flag |= (!util_ops_ispowertwo(bs->sectorspercluster) || bs->sectorspercluster >= 128)))
        SDRIVE_TELEMETRY_ERR("Sectors/Cluster is not a power of two greater than 0 between 1-128\n");
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

void sdrive_fat16_fopen(const char* path, struct sdrive_fat16_file* fp) {
    struct sdrive_fat16_dir root[16];
    for (unsigned i = rootstart; i < rootstart + rootsize; i++) {
        sdrive_drive_readblock((void*) root, i);
        for (unsigned j = 0; j < 16; j++) {
            SDRIVE_TELEMETRY_INF("-------------------------------------------------------\n");
            //SDRIVE_TELEMETRY_INF("Location: 0x%X\n", i * 512 + j * 16);
            SDRIVE_TELEMETRY_INF("Name: %.11s\n", root[j].name);
            SDRIVE_TELEMETRY_INF("First Cluster: %hu\n", root[j].firstclusterlo);
            SDRIVE_TELEMETRY_INF("Directory? %hhu\n", root[j].attr & 0x10);
        }
    }
}

int sdrive_fat16_fini() {
    return 0;
}