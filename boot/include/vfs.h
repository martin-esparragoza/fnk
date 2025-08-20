/**
 * @file vfs.h
 * @brief Static driver outline for the virtual file system
 * @note It's a given but all file paths are ABSOLUTE
 * TODO: Document me well
 */

#ifndef BOOT_INCLUDE_VFS_H_
#define BOOT_INCLUDE_VFS_H_

#include "types.h"
#include "common/include/errc.h"

#define BOOT_VFS_ERRC_DIR_NOT_FOUND COMMON_ERRC_BASE + 0
#define BOOT_VFS_ERRC_DIR_FAILED_CLOSE COMMON_ERRC_BASE + 1
#define BOOT_VFS_ERRC_DIR_NO_NEXT COMMON_ERRC_BASE + 2
#define BOOT_VFS_ERRC_FILE_NOT_FOUND COMMON_ERRC_BASE + 3
#define BOOT_VFS_ERRC_FILE_FAILED_CLOSE COMMON_ERRC_BASE + 4

#define BOOT_VFS_ERRC_DEF_BASE BOOT_VFS_ERRC_FILE_FAILED_CLOSE + 1 // +1 because this must be distinguished from the previous

struct boot_vfs_dir;
typedef struct boot_vfs_dir boot_vfs_dir_t;

struct boot_vfs_file;
typedef struct boot_vfs_file boot_vfs_file_t;

/**
 * @brief Initialization
 * @retval 0 If everything went good
 * @return Value that is not OK if failed
 */
unsigned boot_vfs_init(void);

/**
 * @brief Convert error code to string
 * @note Implementers! You must create the boot_vfs_errctostr_alt array! (see boot/lib/vfs.h for details)
 * @param [in] errc Error code from vfs function
 * @retval NULL if no error code found
 * @return ptr
 */
const char* boot_vfs_errctostr(unsigned errc);

/**
 * @brief Set a dir to be referencing whatever is at path
 * @param [out] dir Modified dir structure
 * @param [in] path Absolute file path
 * @retval 0 If everything went good
 * @return Value that is not OK if failed
 */
unsigned boot_vfs_dir_open(struct boot_vfs_dir* dir, const char* path);

/**
 * @brief Close a directory (prevent them leaks)
 * @param [in] dir Directory to close
 * @retval 0 If everything went good
 * @return Value that is not OK if failed
 */
unsigned boot_vfs_dir_close(struct boot_vfs_dir* dir);

/**
 * @brief Allows for the directory to be iterated on
 * @note This is just to offload this operation in case this is not needed
 * @param [in] dir Directory to transform
 * @retval 0 If everything went good
 * @return Value that is not OK if failed
 */
unsigned boot_vfs_dir_enumerate(struct boot_vfs_dir* dir);

/**
 * @brief Gets the next file in the directory (iteration)
 * @note Requires enumeration before this can happen. Opens a file so it must be later losed. File position indicator must start at the 0th byte.
 * @param [in] dir Directory to target
 * @param [out] file New file pointer to set
 * @retval 0 If everything went good
 * @return Value that is not OK if failed
 */
unsigned boot_vfs_dir_getnextfile(struct boot_vfs_dir* dir, struct boot_vfs_file* file);

/**
 * @brief Sizeof the data structure
 * @note Used to user side allocations
 */
size_t boot_vfs_dir_sizeof(void);

/**
 * @brief Set a file to be referencing whatever is at path
 * @note File position indicator must start at the 0th byte.
 * @param [out] file Modified file structure
 * @param [in] path Absolute file path
 * @retval 0 If everything went good
 * @return Value that is not OK if failed
 */
unsigned boot_vfs_file_open(struct boot_vfs_file* file, const char* path);

/**
 * @brief Close a file (prevent them leaks)
 * @param [in] file File to close
 * @retval 0 If everything went good
 * @return Value that is not OK if failed
 */
unsigned boot_vfs_file_close(struct boot_vfs_file* file);

/**
 * @brief Reads some amount of data starting from internally tracked file location
 * @note It is the implementation's job to cache and stuff. Check your readbytes value!!
 * @param [in] file File target
 * @param [out] buffer Your buffer to write to
 * @param [in] size # of bytes to read
 * @param [out] readbytes # of bytes that were successfully read. Will never read more than requested
 * @retval 0 If everything went good
 * @return Value that is not OK if something bad happened or failed
 */
unsigned boot_vfs_file_read(struct boot_vfs_file* file, void* buffer, size_t size, size_t* readbytes);

/**
 * @brief Move internally tracked file location
 * @param [in] file File target
 * @param [in] offset New location
 * @retval 0 If everything went good
 * @return Value that isnot OK if somethign bad happened or failed
 */
unsigned boot_vfs_file_seek(struct boot_vfs_file* file, uint64_t offset);

/**
 * @brief Sizeof the data structure
 * @note Used to user side allocations
 */
size_t boot_vfs_file_sizeof(void);

/**
 * @brief Clean up
 * @retval 0 If everything went good
 * @return Value that is not OK if failed
 */
unsigned boot_vfs_fini(void);

#endif