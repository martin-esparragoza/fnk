/**
 * @file symtab.h
 * @brief Symbol table data structure and handles
 */

#ifndef ELFTOFNK_INCLUDE_SYMTAB_H_
#define ELFTOFNK_INCLUDE_SYMTAB_H_

#include <bfd.h>
#include <stddef.h>
#include "common/include/errc.h"

#define ELFTOFNK_SYMTAB_ERRC_FAILED_ALLOCATE_MEMORY COMMON_ERRC_BASE + 0
#define ELFTOFNK_SYMTAB_ERRC_FAILED_PARSE           COMMON_ERRC_BASE + 1
#define ELFTOFNK_SYMTAB_ERRC_FAILED_RETRIEVE_SIZE   COMMON_ERRC_BASE + 2
#define ELFTOFNK_SYMTAB_ERRC_COULDNT_FREE           COMMON_ERRC_BASE + 3

typedef struct elftofnk_symtab {
    asymbol** data;
    long numsymbols;
} elftofnk_symtab_t;

/**
 * @brief Sets the data in the symbol table to its correct default values
 * @note Things like elftofnk_symtab_free might not run properly without this
 * @param [in] symtab Symbol table
 */
void elftofnk_symtab_init(struct elftofnk_symtab* symtab);
inline void elftofnk_symtab_init(struct elftofnk_symtab* symtab) {
    symtab->data = NULL;
    symtab->numsymbols = 0;
}

/**
 * @brief Get error string
 * @param [in] errc Error code returned from a call
 * @retval NULL if no error code found
 * @return Pointer to error string
 */
const char* elftofnk_symtab_errctostr(unsigned errc);

/**
 * @brief Load the symbol table onto the heap
 * @note symtab->data must be freed
 * @param [out] symtab Symtab will be set to have data in it. Untrustable if failed
 * @param [in] abfd BFD
 * @retval ELFTOFNK_SYMTAB_ERRC_FAILED_ALLOCATE_MEMORY malloc failed
 * @retval ELFTOFNK_SYMTAB_ERRC_FAILED_PARSE Could not parse the loaded symbol table
 * @retval ELFTOFNK_SYMTAB_ERRC_FAILED_RETRIEVE Failed to get the size of the symbol table
 * @retval 0 If everything went fine
 */
unsigned elftfonk_symtab_load(struct elftofnk_symtab* symtab, bfd* abfd);

/**
 * @brief Attempts to free the data allocated
 * @note Depends on the pointers being initialized to null in order to triger a free. Not running init() could mess things up
 * @param [in] stmtab Symbol table
 * @retval ELFTOFNK_SYMTAB_ERRC_COULDNT_FREE If data could not be freed (not necessairly an error)
 * @retval 0 If everything went fine
 */
unsigned elftofnk_symtab_fini(struct elftofnk_symtab* symtab);

#endif