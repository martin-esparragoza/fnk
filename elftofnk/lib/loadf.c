#include "elftofnk/include/libbfdcrap.h"
#include <bfd.h>
#include "elftofnk/include/loadf.h"
#include <stdlib.h>
#include "common/include/errc.h"

static const char* errcstr[] = {
    [ELFTOFNK_LOADF_ERRC_FAILED_ALLOC - COMMON_ERRC_BASE] =    "Failed to allocate enough memory",
    [ELFTOFNK_LOADF_ERRC_FAILED_GET - COMMON_ERRC_BASE] =      "Failed to get table data",
    [ELFTOFNK_LOADF_ERRC_FAILED_GET_SIZE - COMMON_ERRC_BASE] = "Failed to get size of table/section (something is very wrong)",
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

unsigned elftofnk_loadf_allocsymtabptrs(const bfd* abfd, asymbol** symtab[], long* numsyms) {
    // Intermediate variables so the user doesn't get their stuff broken when we break
    asymbol** isymtab;
    long inumsymbols;

    long symtabsize = bfd_get_symtab_upper_bound((bfd*) abfd); // In bytes
    if (symtabsize > 0) {
        if (!(isymtab = (asymbol**) malloc(symtabsize)))
            return ELFTOFNK_LOADF_ERRC_FAILED_ALLOC;
        if ((inumsymbols = bfd_canonicalize_symtab((bfd*) abfd, isymtab)) < 0)
            return ELFTOFNK_LOADF_ERRC_FAILED_GET;
        // Write the output data if all checks are passed
        *symtab = isymtab;
        *numsyms = inumsymbols;
    } else if (symtabsize < 0)
        return ELFTOFNK_LOADF_ERRC_FAILED_GET_SIZE;

    return 0;
}

unsigned elftofnk_loadf_allocreloctabptrs(const bfd* abfd, const asection* section, arelent** reloctable[], long* numentries) {
    // Intermediate variables so the user doesn't get their stuff broken when we break
    arelent** ireloctab;
    long inumentries;

    long reloctabsize = bfd_get_reloc_upper_bound((bfd*) abfd, (asection*) section); // In bytes
    if (reloctabsize > 0) {
        if (!(ireloctab = (arelent**) malloc(reloctabsize)))
            return ELFTOFNK_LOADF_ERRC_FAILED_ALLOC;
        if ((inumentries = bfd_canonicalize_reloc((bfd*) abfd, (asection*) section, ireloctab, NULL)) < 0)
            return ELFTOFNK_LOADF_ERRC_FAILED_GET;
        // Write the output data if all checks are passed
        *reloctable = ireloctab;
        *numentries = inumentries;
    } else if (reloctabsize < 0)
        return ELFTOFNK_LOADF_ERRC_FAILED_GET_SIZE;

    return 0;
}

unsigned elftofnk_loadf_allocsectiondata(const bfd* abfd, const asection* section, void** data) {
    void* idata;

    // I'm assuming this is trusted? Inline definitions says it probably should be
    long sectionsize = bfd_section_size(section);

    if (sectionsize > 0) {
        if (!(idata = malloc(sectionsize)))
            return ELFTOFNK_LOADF_ERRC_FAILED_ALLOC;

        if (!bfd_get_section_contents((bfd*) abfd, (asection*) section, idata, 0 /* fp offset */, sectionsize))
            return ELFTOFNK_LOADF_ERRC_FAILED_GET;

        *data  = idata;
    }

    return 0;
}