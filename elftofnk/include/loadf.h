/**
 * @file loadf.h
 * @brief Utility functions for loading things
 */

#ifndef ELFTOFNK_INCLUDE_LOADF_H_
#define ELFTOFNK_INCLUDE_LOADF_H_

#include <bfd.h>
#include "common/include/errc.h"

#define ELFTOFNK_LOADF_ERRC_FAILED_ALLOC    COMMON_ERRC_BASE + 0
#define ELFTOFNK_LOADF_ERRC_FAILED_GET      COMMON_ERRC_BASE + 1
#define ELFTOFNK_LOADF_ERRC_FAILED_GET_SIZE COMMON_ERRC_BASE + 2

/**
 * @brief Get error string
 * @param [in] errc Error code
 * @param NULL if no error code found
 * @return Pointer to error string
 */
const char* elftofnk_loadf_errctostr(unsigned errc);

/**
 * @brief Allocate the symbol table pointers onto the heap
 * @note Will do nothing to values and return 0 if there is nothing to allocate
 * @param [in] abfd BFD
 * @param [out] symtab On success this will be set to point to heap allocated memory
 * @param [out] numsyms On success this will be set to the # loaded in
 * @retval ELFTOFNK_LOADF_ERRC_FAILED_ALLOC
 * @retval ELFTOFNK_LOADF_ERRC_FAILED_GET
 * @retval ELFTOFNK_LOADF_ERRC_FAILED_GET_SIZE
 * @retval 0 If everything went fine
 */
unsigned elftofnk_loadf_allocsymtabptrs(const bfd* abfd, asymbol*** symtab, long* numsyms);

/**
 * @brief Allocate the reloctation table pointers onto the heap
 * @note Yes, libbfd does have a function for this but its really ugly + I have to use bfd error handling (which I don't like)
 * @note Will do nothing to values and return 0 if there is nothing to allocate
 * @param [in] abfd BFD
 * @param [in] section Section ptr
 * @param [out] reloctable On success this will be set to point to heap allocated memory
 * @param [out] numentries On success this will be set to the # of relocation table entries
 * @retval ELFTOFNK_LOADF_ERRC_FAILED_ALLOC
 * @retval ELFTOFNK_LOADF_ERRC_FAILED_GET
 * @retval ELFTOFNK_LOADF_ERRC_FAILED_GET_SIZE
 * @retval 0 If everything went fine
 */
unsigned elftofnk_loadf_allocreloctabptrs(const bfd* abfd, const asection* section, arelent*** reloctable, long* numentries);

/**
 * @brief Allocate the sections data to the heap
 * @note Will do nothing to values and return 0 if there is nothing to allocate
 * @param [in] abfd BFD
 * @param [in] section Section ptr
 * @param [out] data On success this will be set to point to the section data
 * @retval ELFTOFNK_LOADF_ERRC_FAILED_ALLOC
 * @retval ELFTOFNK_LOADF_ERRC_FAILED_GET
 * @retval ELFTOFNK_LOADF_ERRC_FAILED_GET_SIZE
 * @retval 0 If everything went fine
 */
unsigned elftofnk_loadf_allocsectiondata(const bfd* abfd, const asection* section, void** data);

#endif