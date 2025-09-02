#include "types.h"
#include "boot/include/vfs.h"
#include "boot/lib/vfs.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h> //< I don't like having to use this but screw the annoying other way you have to do this
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define BOOT_VFS_ERRC_DIRNEXT_FILE_FAIL_OPEN BOOT_VFS_ERRC_DEF_BASE + 0

const char* boot_vfs_errcstr_alt[] = {
    [BOOT_VFS_ERRC_DIRNEXT_FILE_FAIL_OPEN - BOOT_VFS_ERRC_DEF_BASE] = "Failed to open determined file"
};
const size_t boot_vfs_errcstr_alt_sizeof = sizeof(boot_vfs_errcstr_alt) / sizeof(boot_vfs_errcstr_alt[0]);

typedef struct boot_vfs_dir {
    int dfd;
    DIR* dp;
} boot_vfs_dir_t;
typedef struct boot_vfs_file {
    FILE* fp;
} boot_vfs_file_t;

unsigned boot_vfs_init(void) {return 0;}

unsigned boot_vfs_dir_open(struct boot_vfs_dir* dir, const char* path) {
    if ((dir->dp = opendir(path)) == NULL || (dir->dfd = open(path, O_RDONLY | O_DIRECTORY)) == -1)
        return BOOT_VFS_ERRC_DIR_NOT_FOUND;
    return 0;
}

unsigned boot_vfs_dir_close(struct boot_vfs_dir* dir) {
    if (!closedir(dir->dp))
        return BOOT_VFS_ERRC_DIR_FAILED_CLOSE;
    return 0;
}

unsigned boot_vfs_dir_enumerate(struct boot_vfs_dir* dir) {return 0;}

unsigned boot_vfs_dir_getnextfile(struct boot_vfs_dir* dir, struct boot_vfs_file* file) {
    // I hate this code.
    struct dirent* entry;
    struct stat st;
    while ((entry = readdir(dir->dp))) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            fstatat(dir->dfd, entry->d_name, &st, O_RDONLY) == -1 ||
            !S_ISREG(st.st_mode))

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
        return 0;
    }
    return BOOT_VFS_ERRC_DIR_NO_NEXT;
}

size_t boot_vfs_dir_sizeof(void) {
    return sizeof(struct boot_vfs_dir);
}

unsigned boot_vfs_file_open(struct boot_vfs_file* file, const char* path) {
    FILE* interm = fopen(path, "r");
    if (interm) {
        file->fp = interm;
        return 0;
    }
    return BOOT_VFS_ERRC_FILE_NOT_FOUND;
}

unsigned boot_vfs_file_close(struct boot_vfs_file* file) {
    if (fclose(file->fp) != 0)
        return BOOT_VFS_ERRC_FILE_FAILED_CLOSE;
    return 0;
}

unsigned boot_vfs_file_read(struct boot_vfs_file* file, void* buffer, size_t size, size_t* readbytes) {
    *readbytes = fread(buffer, 1, size, file->fp);
    return 0;
}

unsigned boot_vfs_file_seek(struct boot_vfs_file* file, uint64_t offset) {
    fseek(file->fp, offset, SEEK_SET);
    return 0;
}

size_t boot_vfs_file_sizeof(void) {
    return sizeof(struct boot_vfs_file);
}

unsigned boot_vfs_fini(void) {return 0;}