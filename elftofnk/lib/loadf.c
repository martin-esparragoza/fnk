#include <bfd.h>
#include "elftofnk/include/loadf.h"

static const char* errcstr[] = {
    [ELFTOFNK_SYMTAB_ERRC_FAILED_ALLOCATE_MEMORY - COMMON_ERRC_BASE] = "Failed to allocate enough memory",
    [ELFTOFNK_SYMTAB_ERRC_FAILED_PARSE - COMMON_ERRC_BASE] =           "Failed to parse table data",
    [ELFTOFNK_SYMTAB_ERRC_FAILED_RETRIEVE_SIZE - COMMON_ERRC_BASE] =   "Failed to get size of table/section (something is very wrong)",
};

const char* elftofnk_loadf_errctostr(unsigned errc) {
    if (errc >= COMMON_ERRC_BASE) {
        errc -= COMMON_ERRC_BASE;
        if (errc < sizeof(errcstr) / sizeof(errcstr[0]))
            return errcstr[errc];
        // No error code was found
        return NULL;
    }
    return "Ok";
}

unsigned elftofnk_loadf_allocsymtab(bfd* abfd, asymbol** symtab[], long* numsymbols) {

}

unsigned elftofnk_loadf_allocreloctable(bfd* abfd, asection* section, arelent** reloctable[], long* numentries) {
}

unsigned elftofnk_loadf_allocsectiondata(bfd* abfd, asection* section, void** data) {
}