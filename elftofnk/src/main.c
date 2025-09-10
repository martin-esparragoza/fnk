// This program is meant to convert small and simple things to .fnk. A more complicated program will explode probably

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <libgen.h>
#include "elftofnk/include/libbfdcrap.h"
#include <bfd.h>
#include "elftofnk/include/log.h"
#include "elftofnk/include/loadf.h"
#include "common/include/fnkconfig.h"
#include "config.h" // Arch config sorry if this is confusing

#define PARAM_INPUTELF 1
#define PARAM_OUTPUTFNK 2

#define PARAMS_LEN 3

const char* elftofnk_log_level_label_alt[0];
size_t elftofnk_log_level_label_alt_sizeof = 0;

static struct elftofnk_log log;

#define QINFO(format, ...) elftofnk_log_f(&log, ELFTOFNK_LOG_LEVEL_INFO, format, ## __VA_ARGS__)
#define QWARN(format, ...) elftofnk_log_f(&log, ELFTOFNK_LOG_LEVEL_WARNING, format, ## __VA_ARGS__)
#define QERRR(format, ...) elftofnk_log_f(&log, ELFTOFNK_LOG_LEVEL_ERROR, format, ## __VA_ARGS__)

static bfd* abfd;
static FILE* ofile;

static asymbol** symtab;
static long numsyms;

enum {
    I_LJD,
    I_TEXT,
    I_PJD,
    I_DATA,
    I_RODATA,
    I_ENTRY,
    I_BSS
};

typedef struct mappedsection {
    const char* name; // Identifier for when we search for useful sections
    asection* section;
    arelent** reloctable;
    long numrelocentries;
    void* data;
    bool required;
} mappedsection_t;

// This is so we can do some nice recur stuff while still being able to individually manipualte stuff too
static struct mappedsection sectionmap[] = {
    [I_LJD] = {
        .name = ".ljd",
        .required = false
    },
    [I_TEXT] = {
        .name = ".text",
        .required = true
    },
    [I_PJD] = {
        .name = ".pjd",
        .required = false
    },
    [I_DATA] = {
        .name = ".data",
        .required = false
    },
    [I_RODATA] = {
        .name = ".rodata",
        .required = false
    },
    [I_ENTRY] = {
        .name = ".entry",
        .required = false
    },
    [I_BSS] = {
        .name = ".bss",
        .required = false
    }
};

static void cleanup(void) {
    if (ofile)
        fclose(ofile);
    if (abfd)
        bfd_close(abfd);
    if (symtab)
        free(symtab);

    for (
        struct mappedsection* mapped = sectionmap;
        mapped < (sectionmap + sizeof(sectionmap) / sizeof(sectionmap[0]));
        mapped++
    ) {
        if (mapped->reloctable)
            free(mapped->reloctable);
        if (mapped->data)
            free(mapped->data);
    }
}

static void kill(const char* format, ...) {
    va_list args;
    va_start(args, format);
    elftofnk_log_vf(&log, ELFTOFNK_LOG_LEVEL_ERROR, format, args);
    va_end(args);
    cleanup();
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    elftofnk_log_init(&log, stdout);
    bfd_init();

    if (argc != PARAMS_LEN)
        kill("Incorrect format! Format should be %s <inputelf> <outputfnk>\n", argv[0]);

    if (!(abfd = bfd_openr(argv[PARAM_INPUTELF], NULL)) || !bfd_check_format(abfd, bfd_object))
        kill("Failed to open file %s\n", argv[PARAM_INPUTELF]);

    if (!bfd_check_format(abfd, bfd_object))
        kill("File format not supported by libbfd (check if your version of binutils includes support for your desired target)\n");

    if (!(ofile = fopen(argv[PARAM_OUTPUTFNK], "wb")))
        kill("Failed to create handle to file %s\n", argv[PARAM_OUTPUTFNK]);

    unsigned errc; // Just a general reused errc variable

    if ((errc = elftofnk_loadf_allocsymtabptrs(abfd, &symtab, &numsyms)))
        kill("Failed to allocate symbol table. Error: %s\n", elftofnk_loadf_errctostr(errc));

    // Find and map out all sections
    for (asection* section = abfd->sections; section; section = section->next) {
        const char* name = bfd_section_name(section);
        struct mappedsection* mapped;
        for (mapped = sectionmap; mapped < (sectionmap + sizeof(sectionmap) / sizeof(sectionmap[0])); mapped++) {
            if (strcmp(name, mapped->name) == 0) {
                QINFO("Mappable section %s found\n", name);
                mapped->section = section;
                break;
            }
        }
        if (mapped == sectionmap + sizeof(sectionmap) / sizeof(sectionmap[0])) {
            QWARN("Unmapable section found with name \"%s\". Discarding\n", name);
            continue;
        }
    }

    // I want to offload all loading to a different loop because it could become expensive without reason (exit first without doing big stuff)

    // Before that though we have to check if we are not missing any sections
    for (struct mappedsection* mapped = sectionmap; mapped < (sectionmap + sizeof(sectionmap) / sizeof(sectionmap[0])); mapped++) {
        if (!mapped->section) {
            QWARN("Section %s not found. Proceeding\n", mapped->name);
            if (mapped->required)
                kill("Required section %s not found\n", mapped->name);
        }
    }

    // Now we can start loading in everything
    for (struct mappedsection* mapped = sectionmap; mapped < (sectionmap + sizeof(sectionmap) / sizeof(sectionmap[0])); mapped++) {
        if (mapped->section) {
            if ((errc = elftofnk_loadf_allocreloctabptrs(abfd, mapped->section, &mapped->reloctable, &mapped->numrelocentries)))
                kill("Failed to allocate relocation table pointers for section %s. Error: %s\n", mapped->name, elftofnk_loadf_errctostr(errc));
            if ((errc = elftofnk_loadf_allocsectiondata(abfd, mapped->section, &mapped->data)))
                kill("Failed to allocate section data for section %s. Error: %s\n", mapped->name, elftofnk_loadf_errctostr(errc));
        }
    }

    // TODO: Build the relocation table. We can use this to resolve offset dependencies

    if (fflush(ofile))
        kill("Failed to flush to file\n");

    cleanup();
    return 0;


    /*{
        long symboltablesize = bfd_get_symtab_upper_bound(abfd);
        if (symboltablesize >= 0) {
            if (!(symboltable = (asymbol**) malloc(symboltablesize)))
                kill("Failed to allocate memory for symbol table\n");
            if ((numsymbols = bfd_canonicalize_symtab(abfd, symboltable)) < 0)
                kill("Failed to parse symbol table\n");
        } else if (symboltablesize < 0) {
            kill("Failed to retrieve symbol table\n");
        } else {
            WARN("Symbol table has no symbols\n");
        }
    }*/

    // Map all sections
    /*for (asection* section = abfd->sections; section; section = section->next) {
        const char* name = bfd_section_name(section);
        struct mappedsection* mapped;
        for (mapped = sectionmap; mapped < (sectionmap + sizeof(sectionmap) / sizeof(sectionmap[0])); mapped++) {
            if (strcmp(name, mapped->name) == 0) {
                INFO("Mapable section %s found\n", mapped->name);
                mapped->section = section;
                break;
            }
        }
        if (mapped == sectionmap + sizeof(sectionmap) / sizeof(sectionmap[0])) {
            WARN("Unmapable section found with name \"%s\". Discarding\n", name);
            continue;
        }

        if (!(bfd_section_flags(mapped->section) & SEC_RELOC))
            continue;

        long relocationtablesize;
        if ((relocationtablesize = bfd_get_reloc_upper_bound(abfd, mapped->section)) < 0)
            continue;

        if (!(mapped->reloctable = (arelent**) malloc(relocationtablesize)))
            kill("Failed to allocate relocation table for section %s\n", mapped->name);

        if ((mapped->numrelocentries = bfd_canonicalize_reloc(abfd, mapped->section, mapped->reloctable, NULL)) < 0)
            kill("Failed to parse relocation table for section %s\n", mapped->name);
    }

    // Check if we have all sections we need
    for (size_t i = 0; i < sizeof(sectionmap) / sizeof(sectionmap[0]); i++) {
        if (!sectionmap[i].section) {
            if (sectionmap[i].required)
                kill("Required section %s not found\n", sectionmap[i].name);
            WARN("Section %s was not found. Proceeding\n", sectionmap[i].name);
        }
    }

    // Descriptor data
    {
        const uint8_t magic[] = {0xFE, 0xED, 'F', 'N', 'K', 'Y'};

        fwrite(magic, sizeof(magic) / sizeof(magic[0]), 1, ofile);

        // After this point argv[PARAM_OUTPUTFNK] is no longer trustable
        char* name = basename(argv[PARAM_OUTPUTFNK]);
        size_t namesize = 0;
        // Clamp to 12 characters while doing a strlen
        for (char* c = name; *c != '\0' && namesize < COMMON_FNKCONFIG_NAMESIZE; c++, namesize++);

        INFO("Set program name to %.*s\n", namesize, name);

        // Hacky way to get 0s to fill in.
        fwrite(name, namesize, 1, ofile);
        if (namesize < COMMON_FNKCONFIG_NAMESIZE) {
            fseek(ofile, COMMON_FNKCONFIG_NAMESIZE - namesize - 1, SEEK_CUR);
            fwrite("", 1, 1, ofile);
        }
    }*/

    // TODO: Write the temporary section data data structure

    // "Half-resolve" the relocation entries. To do this we collapse basically everything BUT we leave a final offset
    // This allows us to trash the symbol table + just make a simple relocation table for everything

    // The first thing we need is to rip the symbol table out of memory
    /*{
        long symboltablesize = bfd_get_symtab_upper_bound(abfd);
        if (symboltablesize >= 0) {
            if (!(symboltable = (asymbol**) malloc(symboltablesize)))
                kill("Failed to allocate memory for symbol table\n");
            if ((numsymbols = bfd_canonicalize_symtab(abfd, symboltable)) < 0)
                kill("Failed to parse symbol table\n");
        } else if (symboltablesize < 0) {
            kill("Failed to retrieve symbol table\n");
        } else {
            WARN("Symbol table has no symbols\n");
        }
    }

    // Now we can move onto the "half-resolution"
    size_t relocatablesections[] = {I_LJD, I_TEXT, I_PJD, I_DATA, I_RODATA}; // Anything else that requires a relocation should NOT happen
    for (size_t i = 0; i < sizeof(relocatablesections) / sizeof(relocatablesections[0]); i++) {
        struct mappedsection* mapped = &sectionmap[relocatablesections[i]];
        if (!mapped->section)
            continue;
        if (!(bfd_section_flags(mapped->section) & SEC_RELOC))
            continue;

        long relocationtablesize;
        if ((relocationtablesize = bfd_get_reloc_upper_bound(abfd, mapped->section)) < 0)
            continue;

        if (!(mapped->reloctable = (arelent**) malloc(relocationtablesize)))
            kill("Failed to allocate relocation table for section %s\n", mapped->name);

        if ((mapped->numrelocentries = bfd_canonicalize_reloc(abfd, mapped->section, mapped->reloctable, NULL)) < 0)
            kill("Failed to parse relocation table for section %s\n", mapped->name);

        // Now that we have the relocation table we can resolve all relocations

    }*/

        /*
    size_t relsections[] = {I_RELPJD, I_RELAPJD, I_RELLJD, I_RELALJD, I_RELTEXT, I_RELATEXT, I_RELDATA, I_RELADATA};
    for (size_t i = 0; i < sizeof(relsections) / sizeof(relsections[0]); i++) {
        struct mappedsection* sect = &(sectionmap[relsections[i]]);
        if (!sect->section) // Section was not mapped
            continue;

        // Now we can guarantee a jump table
        if (sect->header.sh_type != SHT_REL && sect->header.sh_type != SHT_RELA)
            kill("Corrupted section %s\n", sect->name);

        Elf_Data* data;
        if (!(data = elf_getdata(sect->section, NULL)))
            kill("Failed to get section data for section %s\n", sect->name);

        for (size_t j = 0; j < sect->header.sh_size / sect->header.sh_entsize; j++) {
            switch (sect->header.sh_type) {
                case SHT_REL:
                {
                    GElf_Rel rel;
                    break;
                }
                case SHT_RELA:
                {
                    GElf_Rela rela;
                    gelf_getrela(data, j, &rela);
                    INFO("Symbol: %ld\n", GELF_R_SYM(rela.r_info));
                    symbolmap[symboli++] = GELF_R_SYM(rela.r_info);
                    break;
                }
            }
        }
    }


    if (fflush(ofile))
        kill("Failed to flush to file\n");

    elf_end(ielf);
    close(ifile);
    fclose(ofile);
    */
}