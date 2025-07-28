#include "types.h"
#include "boot/include/vfs.h"
#include "boot/lib/vfs.h"
#include <stdio.h>
#include <fcntl.h> //< I don't like having to use this but screw the annoying other way you have to do this
#include <dirent.h>
#include <string.h>

#define BOOT_VFS_ERRC_DIRNEXT_FILE_FAIL_OPEN BOOT_VFS_ERRC_DEF_END + 0

static const char* errcstr_alt[] = {
    [BOOT_VFS_ERRC_DIRNEXT_FILE_FAIL_OPEN - BOOT_VFS_ERRC_DEF_END] = "Failed to open file as given by directory"
};

typedef struct boot_vfs_dir {

} boot_vfs_dir_t;
    int dfd;
    DIR* dp;
typedef struct boot_vfs_file {
    FILE* fp;
} boot_vfs_file_t;

int boot_vfs_init(void) {return BOOT_VFS_OK;}

int boot_vfs_dir_open(struct boot_vfs_dir* dir, const char* path) {
    if ((dir->dp = opendir(path)) == NULL || (dir->dfd = open(path, O_RDONLY | O_DIRECTORY)) == -1)
        return BOOT_VFS_DIR_NOT_FOUND;
    return BOOT_VFS_OK;
}

int boot_vfs_dir_close(struct boot_vfs_dir* dir) {
    if (!closedir(dir->dp))
        return BOOT_VFS_DIR_FAILED_CLOSE;
    return BOOT_VFS_OK;
}

int boot_vfs_dir_enumerate(struct boot_vfs_dir* dir) {return BOOT_VFS_OK;}

int boot_vfs_dir_getnextfile(struct boot_vfs_dir* dir, struct boot_vfs_file* file) {
    // I hate this code.
    struct dirent* entry;
    struct stat st;
    while ((entry = readdir(dir->dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || fstatat(dir->dfd, entry->d_name, O_RDONLY) == -1 || !S_ISREG(st.st_mode))
            continue;

        // Open that file
        int fd = -1;
        if ((fd = openat(dir->dfd, entry->d_name, O_RDONLY)) == -1)
            return BOOT_VFS_ERRC_DIRNEXT_FILE_FAIL_OPEN;

        FILE* fp = fdopen(fd, "r");
        if (fp == NULL) {
            close(fd);
            return BOOT_VFS_ERRC_DIRNEXT_FILE_FAIL_OPEN;
        }

        file->fp = fp;
        close(fd);
        return BOOT_VFS_ERRC_OK;
    }
    return BOOT_VFS_ERRC_DIR_NO_NEXT;
}


/**
 * @brief Gets the name of the directory
 * @param [in] dir Dir target
 * @param [out] name Output pointer to name. Remains valid until dir is replaced
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_dir_getfilename(struct boot_vfs_dir* dir, const char** name);

/**
 * @brief Sizeof the data structure
 * @note Used to user side allocations
 */
size_t boot_vfs_dir_sizeof(void);

/**
 * @brief Set a file to be referencing whatever is at path
 * @param [in] path Absolute file path
 * @param [out] dir Modified file structure
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_file_open(struct boot_vfs_file* file, const char* path);

int boot_vfs_file_close(struct boot_vfs_file* file);

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
int boot_vfs_file_read(struct boot_vfs_file* file, void* buffer, size_t size, size_t* readbytes);

/**
 * @brief Sizeof the data structure
 * @note Used to user side allocations
 */
size_t boot_vfs_file_sizeof(void);

/**
 * @brief Clean up
 * @retval BOOT_VFS_OK If everything went good
 * @return Value that is not OK if failed
 */
int boot_vfs_fini(void);

#endif