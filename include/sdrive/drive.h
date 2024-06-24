/**
 * @file drive.h
 * @brief Storage medium
 */

/**
 * @brief Initialize driver
 * @return Error code
 */
unsigned char sdrive_drive_init();

/**
 * @brief Destruct driver
 */
unsigned char sdrive_drive_fini();

/**
 * @brief Get LBA size
 * @return -1 if can't fetch block size
 */
short sdrive_drive_getblocksize();

/**
 * @brief Read 1 block and copy it to data
 * @param lba Address
 */
unsigned char sdrive_drive_readblock(void* data, unsigned lba);

/**
 * @brief Write 1 block from data
 * @param lba Address
 */
unsigned char sdrive_drive_writeblock(void* data, unsigned lba);

/**
 * @brief Read num # of blocks and copy it to data
 */
unsigned char sdrive_drive_readmultiblock(void* data, unsigned lba, unsigned short num);

/**
 * @brief Write num # of blocks from data
 */
unsigned char sdrive_drive_writemultiblock(void* data, unsigned lba, unsigned short num);