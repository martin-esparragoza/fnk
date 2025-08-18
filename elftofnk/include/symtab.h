#ifndef ELFTOFNK_INCLUDE_SYMTAB_H_
#define ELFTOFNK_INCLUDE_SYMTAB_H_

#include <bfd.h>
#include "common/include/errc.h"

#define ELFTOFNK_SYMTAB_ERRC_FAILED_ALLOCATE_MEMORY COMMON_ERRC_BASE + 0
#define ELFTOFNK_SYMTAB_ERRC_FAILED_PARSE           COMMON_ERRC_BASE + 1
#define ELFTOFNK_SYMTAB_ERRC_FAILED_RETRIEVE_SIZE   COMMON_ERRC_BASE + 2

typedef struct elftofnk_symtab {
    asymbol** data;
    long numsymbols;
} elftofnk_symtab_t;

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
 * @return errc
 */
unsigned elftfonk_symtab_load(struct elftofnk_symtab* symtab, bfd* abfd);

#endif