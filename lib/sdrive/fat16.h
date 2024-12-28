/**
 * @file fat16.h
 * @brief Private definitions
 * // TODO: Grouping
 */

#ifndef LIB_SDRIVE_FAT16_H_
#define LIB_SDRIVE_FAT16_H_

#include "include/sdrive/fat16.h"
#include "attr.h"
#include <stdint.h>
#include <stddef.h>

#define SDRIVE_FAT16_DIR_ATTR_READ_ONLY      0x01
#define SDRIVE_FAT16_DIR_ATTR_HIDDEN         0x02
#define SDRIVE_FAT16_DIR_ATTR_SYSTEM         0x04
#define SDRIVE_FAT16_DIR_ATTR_VOLUME_ID      0x08
#define SDRIVE_FAT16_DIR_ATTR_DIRECTORY      0x10
#define SDRIVE_FAT16_DIR_ATTR_ARCHIVE        0x20
#define SDRIVE_FAT16_DIR_ATTR_LONG_FILE_NAME 0x0F

struct sdrive_fat16_file {
    uint_fast16_t startingcluster;
    uint_fast16_t nextcluster;
    uint_fast16_t size; //< Clusters
    uint_fast16_t clustersread;
};

struct sdrive_fat16_dir {
    uint_fast16_t startingcluster;
};

typedef struct INCLUDE_COMP_ATTR_PACKED sdrive_fat16_bs {
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
} sdrive_fat16_bs_t;

typedef struct INCLUDE_COMP_ATTR_PACKED sdrive_fat16_dir_sfn {
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
} sdrive_fat16_dir_sfn_t;

typedef struct INCLUDE_COMP_ATTR_PACKED sdrive_fat16_dir_lfn {
    uint8_t ord;
    uint16_t name1[5];
    uint8_t attribute;
    uint8_t type;
    uint8_t chksum;
    uint16_t name2[6];
    uint16_t firstclusterlo;
    uint16_t name3[2];
} sdrive_fat16_dir_lfn_t;

uint8_t getchksum(struct sdrive_fat16_dir_sfn* dir);

/**
 * @brief Treat a buffer as a directory listing and grab SFN entry from it
 * 
 * @param file File to search for
 * @param outsfn SFN to output to (i already used the name SFN im lazy)
 * @param buffer Search buffer
 * @param size_t Lenth of search buffer
 */
int sdrive_fat16_open(const char* file, struct sdrive_fat16_dir_sfn* outsfn, void* buffer, size_t bufferlen);

/**
 * @brief Get SFN from root
 * Handles buffer creation and reading
 * I can avoid the memcpy yeah but like me no do
 */
int sdrive_fat16_root_open(const char* file, struct sdrive_fat16_dir_sfn* sfn);

/**
 * @brief Convert sfn to fp
 */
int sdrive_fat16_createfpfromsfn(struct sdrive_fat16_file* fp, struct sdrive_fat16_dir_sfn* sfn);

#endif