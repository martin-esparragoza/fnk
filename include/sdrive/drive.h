/**
 * @file drive.h
 * @brief Storage medium
 */

#ifndef INCLUDE_SDRIVE_DRIVE_H_
#define INCLUDE_SDRIVE_DRIVE_H_

#include <stdint.h>

/**
 * @brief Initialize driver
 * @return Error code
 */
int sdrive_drive_init();

/**
 * @brief Destruct driver
 */
int sdrive_drive_fini();

/**
 * @brief Get LBA size
 * @return -1 if can't fetch block size
 */
uint_fast16_t sdrive_drive_getblocksize();

/**
 * @brief Read 1 block and copy it to data
 * @param lba Address
 * @return # of blocks read (0 OR -1 if error)
 */
int sdrive_drive_readblock(void* data, unsigned lba);

/**
 * @brief Write 1 block from data
 * @param lba Address
 * @return # of blocks read (0 OR -1 if error)
 */
int sdrive_drive_writeblock(void* data, unsigned lba);

/**
 * @brief Read num # of blocks and copy it to data
 * 
 * @return # of blocks read (-1 if error)
 */
int_fast16_t sdrive_drive_readmultiblock(void* data, unsigned lba, uint_fast16_t num);

/**
 * @brief Write num # of blocks from data
 * 
 * @return # of blocks read (-1 if error)
 */
int_fast16_t sdrive_drive_writemultiblock(void* data, unsigned lba, uint_fast16_t num);

#endif