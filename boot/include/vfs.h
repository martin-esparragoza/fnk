/**
 * @file vfs.h
 * @brief Static driver outline for the virtual file system
 * @note It's a given but all file paths are ABSOLUTE
 */

#ifndef BOOT_INCLUDE_VFS_H_
#define BOOT_INCLUDE_VFS_H_

#include "types.h"

#define BOOT_VFS_OK 0

struct boot_vfs_dir;
typedef struct boot_vfs_dir boot_vfs_dir_t;

struct boot_vfs_file;
typedef struct boot_vfs_file boot_vfs_file_t;

/**
 * @brief Initialization
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_init(void);

/**
 * @brief Convert returned error code to string
 * @param [in] errc Error code from vfs function
 * @retval NULL if no error code found
 * @return ptr
 */
const char* boot_vfs_errctostr(int errc);

/**
 * @brief Set a dir to be referencing whatever is at path
 * @param [in] path Absolute file path
 * @param [out] dir Modified dir structure
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_opendir(const char* path, struct boot_vfs_dir* dir);

/**
 * @brief Allows for the directory to be iterated on
 * @note This is just to offload this operation in case this is not needed
 * @param [in] dir Directory to transform
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_dir_enumerate(struct boot_vfs_dir* dir);

/**
 * @brief Gets the next file in the directory (iteration)
 * @note Requires enumeration before this can happen
 * @param [in] dir Directory to target
 * @param [out] file New file pointer to set
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_dir_getnextfile(struct boot_vfs_dir* dir, struct boot_vfs_file* file);


/**
 * @brief Gets the name of the directory
 * @param [in] dir Dir target
 * @param [out] name Output pointer to name. Remains valid until dir is replaced
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_dir_getfilename(struct boot_vfs_dir* dir, const char** name);

/**
 * @brief Set a file to be referencing whatever is at path
 * @param [in] path Absolute file path
 * @param [out] dir Modified file structure
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_openfile(const char* path, struct boot_vfs_file* file);

/**
 * @brief Gets the name of the file
 * @param [in] file File target
 * @param [out] name Output pointer to name. Remains valid until file is replaced
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_file_getfilename(struct boot_vfs_file* file, const char** name);

/**
 * @brief Reads some amount of data
 * @note It is the implementation's job to cache and stuff. Check your readbytes value!!
 * @param [in] file File target
 * @param [out] buffer Your buffer to write to
 * @param [in] size # of bytes to read
 * @param [out] readbytes # of bytes that were successfully read. Will never read more than requested
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if something bad happened or failed
 */
int boot_vfs_file_read(struct boot_vfs_file* file, void* buffer, size_t size, size_t* readbytes)

/**
 * @brief Clean up
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_fini(void);

#endif