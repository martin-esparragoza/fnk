#ifndef BOOT_LIB_VFS_H_
#define BOOT_LIB_VFS_H_

extern const char* boot_vfs_errcstr_alt[]; ///< The implementer must define this array. Remember to use BOOT_VFS_ERRC_DEF_END

/**
 * @brief Architecture specific definition
 * @param [in] errc Error code
 * @retval NULL if no error code found
 * @return ptr
 * Add your own error codes who cares
 */
const char* boot_vfs_errctostr_alt(int errc);

#endif