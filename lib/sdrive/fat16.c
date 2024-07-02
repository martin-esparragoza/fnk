#include "../../include/sdrive/fat16.h"
#include "../../include/sdrive/drive.h"
#include "../../include/sdrive/telemetry.h"
#include "../../include/arch/config.h"
#include <stdint.h>

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
}* bootsector;


int sdrive_fat16_init(unsigned lba_bootsector) {
    uint_fast16_t blocksize = sdrive_drive_getblocksize();
    bootsector = __builtin_alloca(blocksize);
    unsigned ret = sdrive_drive_readblock(bootsector, lba_bootsector);

    if (!ret)
        return ret;
    
    // Print out boot sector values
#ifdef ARCH_CONFIG_VERBOSE 
    SDRIVE_TELEMETRY_LOG("oemname: %.8s\n", bootsector->oemname);
    SDRIVE_TELEMETRY_LOG("Bytes/Sector: %hu\n", bootsector->bytespersector);
    SDRIVE_TELEMETRY_LOG("Bytes/Cluster: %hu\n", bootsector->bytespercluster);
    SDRIVE_TELEMETRY_LOG("Reserved Sectors: %hhu\n", bootsector->reservedsectors);
    SDRIVE_TELEMETRY_LOG("# of FATs: %hhu\n", bootsector->numfats);
    SDRIVE_TELEMETRY_LOG("Root Entry Size: %hu\n", bootsector->rootentrycount);
    SDRIVE_TELEMETRY_LOG("Total Sectors (16 bit): %hu\n", bootsector->totalsectors16);
    SDRIVE_TELEMETRY_LOG("Media Type: 0x%02hhX\n", bootsector->mediatype);
    SDRIVE_TELEMETRY_LOG("FAT size: %hu\n", bootsector->fatsize16);
    SDRIVE_TELEMETRY_LOG("Sectors/Track: %hu\n", bootsector->sectorspertrack);
    SDRIVE_TELEMETRY_LOG("# Of Disk Heads: %hu\n", bootsector->numheads);
    SDRIVE_TELEMETRY_LOG("Hidden Sectors: %u\n", bootsector->hiddensectors);
    SDRIVE_TELEMETRY_LOG("Total Sectors (32 bit): %u\n", bootsector->totalsectors32);
    SDRIVE_TELEMETRY_LOG("Drive # (BIOS + IBM PC): 0x%02hhX\n", bootsector->drivenum);
    SDRIVE_TELEMETRY_LOG("ExSig: %hhu\n", bootsector->extendedsignature);
    SDRIVE_TELEMETRY_LOG("ID: %u\n", bootsector->id);
    SDRIVE_TELEMETRY_LOG("Label: %.11s\n", bootsector->label);
    SDRIVE_TELEMETRY_LOG("Fat Type (unreliable): %.8s\n", bootsector->strfattype);
    SDRIVE_TELEMETRY_LOG("0x55AA Existance: 0x%04hX\n", bootsector->signature);
#endif

    return 0;
}



int sdrive_fat16_fini() {
    return 0;
}