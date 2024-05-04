/**
 * @file edisk.h
 * @brief Disk driver
 * Disk driver that will be used.
 * Probably a good idea to implement this in arch
 * Modeled around SCSI
 */

#ifndef INCLUDE_DRIVERS_EDISK_H_
#define INCLUDE_DRIVERS_EDISK_H_

#define DRIVERS_DISK_ERRC_OK 0

// Error type -> unsigned

/**
 * Convert error code (unsigned) to string return value
 */
const char* drivers_disk_errctostr(unsigned errc);

/**
 * @brief Reset the disk
 */
unsigned drivers_disk_swreset();

/**
 * @brief Initialize disk
 */
unsigned drivers_disk_init();

/**
 * @brief Stop current operation
 */
unsigned drivers_disk_stop();

/**
 * @brief Set block size
 * Error code returned upon invalid block size given
 */
unsigned drivers_disk_setblocklen();

/**
 * @brief Get block size
 */
unsigned drivers_disk_getblocklen(unsigned* len);

/**
 * @param block Block buffer
 */
unsigned drivers_disk_readblock(void* block);

unsigned drivers_disk_readmultiblockull(void* block, unsigned long long num);
unsigned drivers_disk_readmultiblockul(void* block, unsigned long num);
unsigned drivers_disk_readmultiblocku(void* block, unsigned num);
unsigned drivers_disk_readmultiblockus(void* block, unsigned short num);
unsigned drivers_disk_readmultiblockuc(void* block, unsigned char num);

/**
 * @param block Data to write to that block
 */
unsigned drivers_disk_writeblock(void* block);

unsigned drivers_disk_writemultiblockull(void* block, unsigned long long num);
unsigned drivers_disk_writemultiblockul(void* block, unsigned long num);
unsigned drivers_disk_writemultiblocku(void* block, unsigned num);
unsigned drivers_disk_writemultiblockus(void* block, unsigned short num);
unsigned drivers_disk_writemultiblockuc(void* block, unsigned char num);

#endif
