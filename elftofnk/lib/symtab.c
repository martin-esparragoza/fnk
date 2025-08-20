#include <bfd.h>
#include <stddef.h>
#include <stdlib.h>
#include "elftofnk/include/symtab.h"
#include "elftofnk/include/log.h"
#include "common/include/errc.h"

static const char* errcstr[] = {
    [ELFTOFNK_SYMTAB_ERRC_FAILED_ALLOCATE_MEMORY - COMMON_ERRC_BASE] = "Could not allocate memory for symbol table",
    [ELFTOFNK_SYMTAB_ERRC_FAILED_PARSE - COMMON_ERRC_BASE] =           "Could not parse symbol table",
    [ELFTOFNK_SYMTAB_ERRC_FAILED_RETRIEVE_SIZE - COMMON_ERRC_BASE] =   "Failed to retrieve symbol table size",
    [ELFTOFNK_SYMTAB_ERRC_COULDNT_FREE - COMMON_ERRC_BASE] =           "Could not free symbol table (maybe it wasn't allocated in the first place?)"
};

const char* elftofnk_symtab_errctostr(unsigned errc) {
    if (errc >= COMMON_ERRC_BASE) {
        errc -= COMMON_ERRC_BASE;
        if (errc < sizeof(errcstr) / sizeof(errcstr[0]))
            return errcstr[errc];
        // No error code was found
        return NULL;
    }
    return "Ok";
}

unsigned elftfonk_symtab_load(struct elftofnk_symtab* symtab, bfd* abfd) {
    long symboltablesize = bfd_get_symtab_upper_bound(abfd);
    if (symboltablesize >= 0) {
        if (!(symtab->data = (asymbol**) malloc(symboltablesize)))
            return ELFTOFNK_SYMTAB_ERRC_FAILED_ALLOCATE_MEMORY;
        if ((symtab->numsymbols = bfd_canonicalize_symtab(abfd, symboltable)) < 0)
            return ELFTOFNK_SYMTAB_ERRC_FAILED_PARSE;
    } else if (symboltablesize < 0) {
        return ELFTOFNK_SYMTAB_ERRC_FAILED_RETRIEVE;
    } else
        ELFTOFNK_LOG_WARN("Symbol table has no symbols\n");
    return 0;
}

unsigned elftofnk_symtab_fini(struct elftofnk_symtab* symtab) {
    if (symtab->data) {
        free(symtab->data);
        return 0;
    }
    return ELFTOFNK_SYMTAB_ERRC_COULDNT_FREE;
}