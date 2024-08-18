// Has general FAT16 stuff

#include "sdrive/fat16.h"
#include "../include/sdrive/fat16.h"
#include "../include/sdrive/drive.h"
#include "../include/sdrive/telemetry.h"
#include "../include/arch/config.h"
#include "util/memdump.h"
#include "util/ops.h"
#include "util/flinkedlist.h"
#include "util/string.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern struct util_memdump md;

struct sdrive_fat16_bs* bs;

static const char* sdrive_fat16_errcstr[] = {
    [SDRIVE_FAT16_ERRC_OK] = "Ok",
    [SDRIVE_FAT16_ERRC_CORRUPTBS] = "Boot segment is corrupted",
    [SDRIVE_FAT16_ERRC_READ_FAIL] = "Failed to read sector(s)",
    [SDRIVE_FAT16_ERRC_FILE_NOT_FOUND] = "Failed to find file",
    [SDRIVE_FAT16_ERRC_INVALID_PATH] = "Invalid file",
    [SDRIVE_FAT16_ERRC_FATSZ_TOO_SMALL] = "FATSZ (buffer allocated) too small for expected FAT",
    [SDRIVE_FAT16_ERRC_CORRUPTED_FILE] = "File corrupted",
    [SDRIVE_FAT16_ERRC_EOF] = "End of file reached",
    [SDRIVE_FAT16_ERRC_NOT_A_FILE] = "Attempted to open a file that is not one",
    [SDRIVE_FAT16_ERRC_NOT_A_DIR] = "Ammpted to open a directory that is not one",
    [SDRIVE_FAT16_ERRC_EOD] = "End of directory reached",
    [SDRIVE_FAT16_ERRC_WARN_FATSZ_TOO_LARGE] = "FATSZ (buffer allocated) too large for expected FAT"
};

static uint_fast32_t fatstart, fatsize, rootstart, rootsize, datastart, datasize, numclusters;
static uint_fast16_t bytespersector, sectorspercluster;
static __attribute__((aligned(8))) uint16_t fat[ARCH_CONFIG_FAT16_FATSZ / 2]; // Divided by 2 because FATSZ is supposed to be in bytes

const char* sdrive_fat16_errctostr(int errc) {
    if (errc < sizeof(sdrive_fat16_errcstr) / sizeof(sdrive_fat16_errcstr[0]) && errc > 0)
        return sdrive_fat16_errcstr[errc];

    // Default errc not found
    return NULL;
}

int sdrive_fat16_init(unsigned lba_bootsector) {
    uint_fast16_t blocksize = sdrive_drive_getblocksize();
    bs = __builtin_alloca_with_align(blocksize, 8);
    if ((md.num_blocks_read_bs = sdrive_drive_readblock(bs, lba_bootsector)) != 1)
        return SDRIVE_FAT16_ERRC_READ_FAIL;

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
    bytespersector = bs->bytespersector;
    sectorspercluster = bs->sectorspercluster;
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
    SDRIVE_TELEMETRY_INF("0xAA55 Existance: 0x%04hX\n", bs->signature);
    SDRIVE_TELEMETRY_INF("FAT (region) Start: %d\n", fatstart);
    SDRIVE_TELEMETRY_INF("FAT (region) Size (sectors): %d\n", fatsize);
    SDRIVE_TELEMETRY_INF("Root Directory Start: %d\n", rootstart);
    SDRIVE_TELEMETRY_INF("Root Directory Size (sectors): %d\n", rootsize);
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
        return SDRIVE_FAT16_ERRC_CORRUPTBS;
    
    // TODO: Ponder if its even good here to like print and stuff
    const uint_fast32_t fatszexpected = bs->fatsize16 * bytespersector;
    // Get the first FAT and read that in
    if (ARCH_CONFIG_FAT16_FATSZ < fatszexpected) {
        SDRIVE_TELEMETRY_ERR("FATSZ too small for this volume. Expected %u bytes got %u bytes\n", fatszexpected, ARCH_CONFIG_FAT16_FATSZ);
        return SDRIVE_FAT16_ERRC_FATSZ_TOO_SMALL;
    } else if (ARCH_CONFIG_FAT16_FATSZ > fatszexpected) {
        return SDRIVE_FAT16_ERRC_WARN_FATSZ_TOO_LARGE;
        SDRIVE_TELEMETRY_WRN("FATSZ too large for this volume. Continuing. Expected %u bytes and got %u bytes\n", fatszexpected, ARCH_CONFIG_FAT16_FATSZ);
    }

    if (sdrive_drive_readmultiblock((void*) fat, fatstart + bs->fatsize16 * ARCH_CONFIG_FAT16_FAT, bs->fatsize16) != bs->fatsize16)
        return SDRIVE_FAT16_ERRC_READ_FAIL;
    
    return 0;
}

inline uint8_t getchksum(struct sdrive_fat16_dir_sfn* dir) {
    uint8_t sum = 0;
    for (uint_fast8_t i = 0; i < sizeof(dir->name) / sizeof(dir->name[0]); i++)
        sum = (sum >> 1) + (sum << 7) + dir->name[i];
    return sum;
}

/**
 * The default state. Reads SFNs however once a LFN is detected it pivots states to process it
 */
#define sdrive_fat16_open_STATE_READING_SFN 0
/**
 * Processes newlyfound LFNs
 */
#define sdrive_fat16_open_STATE_READING_LFN 1

// Grabs us a SFN for a file we want given a buffer
int sdrive_fat16_open(const char* file, struct sdrive_fat16_dir_sfn* outsfn, void* buffer, size_t bufferlen) {
    uint_fast8_t filenamelen = util_strlen(file); // Max length of anything in FAT is 255 anyway

    if (filenamelen == 0)
        return SDRIVE_FAT16_ERRC_INVALID_PATH;

    // Read all directories loop (by SFNs first)
    uint_fast8_t state = sdrive_fat16_open_STATE_READING_SFN;
    uint_fast8_t lfnindex = filenamelen;
    bool lfnbad = false; // Set to true when lfn is found to be invalid
    bool lfnpaddingused = false; // There could be some of the text not being used

    for (struct sdrive_fat16_dir_sfn* sfn = buffer; ((uintptr_t) sfn) < ((uintptr_t) buffer) + bufferlen; sfn++) {
        // Duct tape TODO:
        if (sfn->name[0] == 0)
            return SDRIVE_FAT16_ERRC_EOD;

        switch (state) {
            case sdrive_fat16_open_STATE_READING_SFN: sdrive_fat16_open_STATE_READING_SFN_L:
                if (sfn->attr & SDRIVE_FAT16_DIR_ATTR_LONG_FILE_NAME) {
                    // Transition stuffs
                    state = sdrive_fat16_open_STATE_READING_LFN;
                    lfnindex = filenamelen - 1;
                    lfnbad = lfnpaddingused = false;
                    goto sdrive_fat16_open_STATE_READING_LFN_L;
                }
                
                // Check the SFN for existance
                if (filenamelen < 11) { // We shouldn't check if its going to be a lfn anyway (yes you could further optimize this but this is a good lazy solution)
                    for (uint_fast8_t i = 0; i < 11; i++) { // 11 is SFN name length
                        if (file[i] != sfn->name[i]) {
                            if ((sfn->name[i] == ' ' || i == 10) && file[i] == '\0') {
                                *outsfn = *sfn;
                                return SDRIVE_FAT16_ERRC_OK;
                            }
                            
                            break;
                        }
                    }
                }
                break;

            case sdrive_fat16_open_STATE_READING_LFN: sdrive_fat16_open_STATE_READING_LFN_L:
                if (!(sfn->attr & SDRIVE_FAT16_DIR_ATTR_LONG_FILE_NAME)) {
                    if (!lfnbad) {
                        *outsfn = *sfn;
                        return SDRIVE_FAT16_ERRC_OK;
                    }
                    state = sdrive_fat16_open_STATE_READING_SFN;
                    break;
                }

                if (lfnbad)
                    break;

                struct sdrive_fat16_dir_lfn* lfn = (void*) sfn;

                uint16_t* p = lfn->name3 + 1; // 2 is name3 length
                while (1) {
                    uint16_t val = *p;
#ifdef ARCH_CONFIG_BIG_ENDIAN
                    val = __builtin_bswap16(val);
#endif
                    char c = (const char) val;
                    
                    if (!(c == 0 || c == (char) 255) && !lfnpaddingused) {
                        lfnpaddingused = true;
                    }

                    if (lfnpaddingused) {
                        if (c != file[lfnindex]) {
                            lfnbad = true;
                            break;
                        } else {
                            lfnindex--;
                        }
                    }

                    if (p == lfn->name3) {
                        p = lfn->name2 + 5; // 6 is name2 length
                    } else if (p == lfn->name2) {
                        p = lfn->name1 + 4; // 5 is name1 length
                    } else if (p == lfn->name1) {
                        break;
                    } else {
                        p--;
                    }
                }
                break;
        }
    }

    return SDRIVE_FAT16_ERRC_FILE_NOT_FOUND;
}

// Yes i know how to avoid the memcpy but this file is already heinous enough thank you.
// This function creates the buffer and stuff and handles the "optimized" reading
int sdrive_fat16_root_open(const char* file, struct sdrive_fat16_dir_sfn* sfn) {
    void* buffer = __builtin_alloca_with_align(bytespersector * ARCH_CONFIG_FAT16_SECTORBUFFER_SZ, 8);
    // For consistency and loopability we must convert this to sectors and not use clusters
    uint_fast32_t dirstart = rootstart;
    uint_fast32_t dirsize = rootsize;
    int errc = SDRIVE_FAT16_ERRC_OK;

    while (dirsize > 0) {
        int bytesread = 0;
        
        // This is just us clamping the size of what we read to not overflow the buffer
        uint_fast32_t sectorstoread = util_ops_min(dirsize, ARCH_CONFIG_FAT16_SECTORBUFFER_SZ);
        if ((bytesread = sdrive_drive_readmultiblock(buffer, dirstart, sectorstoread) * bytespersector) <= 0) {
            return SDRIVE_FAT16_ERRC_READ_FAIL;
        }
        dirstart += ARCH_CONFIG_FAT16_SECTORBUFFER_SZ;
        dirsize -= ARCH_CONFIG_FAT16_SECTORBUFFER_SZ; 

        
        errc = sdrive_fat16_open(file, sfn, buffer, bytespersector * ARCH_CONFIG_FAT16_SECTORBUFFER_SZ);
        if (errc == SDRIVE_FAT16_ERRC_EOD) { // Jank method..
            break;
        } else if (errc != SDRIVE_FAT16_ERRC_FILE_NOT_FOUND) {
            return errc;
        }
    }
    return SDRIVE_FAT16_ERRC_FILE_NOT_FOUND;
}

int sdrive_fat16_createfpfromsfn(struct sdrive_fat16_file* fp, struct sdrive_fat16_dir_sfn* sfn) {
#ifdef ARCH_CONFIG_BIG_ENDIAN
    sfn->firstclusterlo = __builtin_bswap16(sfn->firstclusterlo);
    sfn->filesize = __builtin_bswap32(sfn->filesize);
#endif

    if (sfn->attr & SDRIVE_FAT16_DIR_ATTR_DIRECTORY)
        return SDRIVE_FAT16_ERRC_NOT_A_FILE;

    fp->startingcluster = sfn->firstclusterlo;
    fp->nextcluster = fp->startingcluster;
    
    // Garbage floor I can't think rn TODO:
    fp->size = sfn->filesize / (bytespersector * sectorspercluster);
    if (sfn->filesize % bytespersector % sectorspercluster != 0)
        fp->size++;


    fp->clustersread = 0;
    if (fp->nextcluster <= 1 && fp->nextcluster | fp->size /* Jank ahh hack */)
        return SDRIVE_FAT16_ERRC_CORRUPTED_FILE;
    return SDRIVE_FAT16_ERRC_OK;
}

int sdrive_fat16_createdpfromsfn(struct sdrive_fat16_dir* dp, struct sdrive_fat16_dir_sfn* sfn) {
#ifdef ARCH_CONFIG_BIG_ENDIAN
    sfn->firstclusterlo = __builtin_bswap16(sfn->firstclusterlo);
#endif

    if (!(sfn->attr & SDRIVE_FAT16_DIR_ATTR_DIRECTORY))
        return SDRIVE_FAT16_ERRC_NOT_A_DIR;

    dp->startingcluster = sfn->firstclusterlo;

    if (dp->startingcluster <= 1)
        return SDRIVE_FAT16_ERRC_CORRUPTED_FILE;
    
    return SDRIVE_FAT16_ERRC_OK;
}

int sdrive_fat16_root_file_open(const char* file, struct sdrive_fat16_file* fp) {
    struct sdrive_fat16_dir_sfn sfn;
    int errc = SDRIVE_FAT16_ERRC_OK;
    if ((errc = sdrive_fat16_root_open(file, &sfn)) > SDRIVE_FAT16_ERRC_OK)
        return errc;

    if ((errc = sdrive_fat16_createfpfromsfn(fp, &sfn)) > SDRIVE_FAT16_ERRC_OK)
        return errc;
    
    return SDRIVE_FAT16_ERRC_OK;
}

int sdrive_fat16_root_dir_open(const char* file, struct sdrive_fat16_dir* dp) {
    struct sdrive_fat16_dir_sfn sfn;
    int errc = SDRIVE_FAT16_ERRC_OK;
    if ((errc = sdrive_fat16_root_open(file, &sfn)) > SDRIVE_FAT16_ERRC_OK)
        return errc;
#ifdef ARCH_CONFIG_BIG_ENDIAN
    sfn.firstclusterlo = __builtin_bswap16(sfn.firstclusterlo);
#endif

    if (!(sfn.attr & SDRIVE_FAT16_DIR_ATTR_DIRECTORY))
        return SDRIVE_FAT16_ERRC_NOT_A_DIR;

    dp->startingcluster = sfn.firstclusterlo;

    if (dp->startingcluster <= 1)
        return SDRIVE_FAT16_ERRC_CORRUPTED_FILE;
    
    return SDRIVE_FAT16_ERRC_OK;
}

int sdrive_fat16_file_readcluster(struct sdrive_fat16_file* fp, void* buffer) {
    if (fp->clustersread >= fp->size)
        return SDRIVE_FAT16_ERRC_EOF;

    if (sdrive_drive_readmultiblock(buffer, datastart + (fp->nextcluster - 2) * sectorspercluster, sectorspercluster) != sectorspercluster)
        return SDRIVE_FAT16_ERRC_READ_FAIL;
    
    // Update next
    uint_fast16_t newnext = fat[fp->nextcluster];
    fp->nextcluster = newnext;
    fp->clustersread++;

    return SDRIVE_FAT16_ERRC_OK;
}

int sdrive_fat16_file_open(const char* file, struct sdrive_fat16_dir* dp, struct sdrive_fat16_file* fp) {
    // Buffer loop & stuff
    struct sdrive_fat16_dir_sfn sfn;
    int errc = SDRIVE_FAT16_ERRC_OK;
    void* buffer = __builtin_alloca_with_align(sdrive_fat16_getbytespercluster(), 8);

    // What we can do here is create basically a file so we can use file_readcluster. We just need to make the size essentially infinite
    struct sdrive_fat16_file reader = {
        .startingcluster = dp->startingcluster,
        .nextcluster = dp->startingcluster,
        .size = UINT_FAST16_MAX,
        .clustersread = 0
    };

    while (1) {
        // Read into buffer
        if ((errc = sdrive_fat16_file_readcluster(&reader, buffer)) > SDRIVE_FAT16_ERRC_OK) {
            return errc;
        }

        errc = sdrive_fat16_open(file, &sfn, buffer, sdrive_fat16_getbytespercluster());

        if (errc == SDRIVE_FAT16_ERRC_EOD) { // EOD reached -> File couldnt be found then
            return SDRIVE_FAT16_ERRC_FILE_NOT_FOUND;
        } else if (errc == SDRIVE_FAT16_ERRC_OK) { // File found -> Return the file
            if ((errc = sdrive_fat16_createfpfromsfn(fp, &sfn)) > SDRIVE_FAT16_ERRC_OK)
                return errc;
            return SDRIVE_FAT16_ERRC_OK;
        }
    }

    return SDRIVE_FAT16_ERRC_FILE_NOT_FOUND;
}

int sdrive_fat16_dir_open(const char* file, struct sdrive_fat16_dir* dp, struct sdrive_fat16_dir* dpout) {
    // Buffer loop & stuff
    struct sdrive_fat16_dir_sfn sfn;
    int errc = SDRIVE_FAT16_ERRC_OK;
    void* buffer = __builtin_alloca_with_align(sdrive_fat16_getbytespercluster(), 8);

    struct sdrive_fat16_file reader = {
        .startingcluster = dp->startingcluster,
        .nextcluster = dp->startingcluster,
        .size = UINT_FAST16_MAX,
        .clustersread = 0
    };

    while (1) {
        // Read into buffer
        if ((errc = sdrive_fat16_file_readcluster(&reader, buffer)) > SDRIVE_FAT16_ERRC_OK)
            return errc;

        errc = sdrive_fat16_open(file, &sfn, buffer, sdrive_fat16_getbytespercluster());

        if (errc == SDRIVE_FAT16_ERRC_EOD) { // EOD reached -> File couldn't be found
            return SDRIVE_FAT16_ERRC_FILE_NOT_FOUND;
        } else if (errc == SDRIVE_FAT16_ERRC_OK) { // File found -> Return the directory
            if ((errc = sdrive_fat16_createdpfromsfn(dpout, &sfn)) > SDRIVE_FAT16_ERRC_OK)
                return errc;
            return SDRIVE_FAT16_ERRC_OK;
        }
    }

    return SDRIVE_FAT16_ERRC_FILE_NOT_FOUND;
}

uint_fast32_t sdrive_fat16_getbytespercluster() {
    return bytespersector * sectorspercluster;
}

inline size_t sdrive_fat16_file_sizeof() {
    return sizeof(struct sdrive_fat16_file);

}

inline size_t sdrive_fat16_dir_sizeof() {
    return sizeof(struct sdrive_fat16_file);
}


int sdrive_fat16_fini() {
    return 0;
}