#include <stdio.h>
#include <libelf.h>
#include <gelf.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "tool/log.h"

const char* log_loglevel_label_alt[0];
size_t log_loglevel_label_alt_sizeof = 0;

struct log_logger logger;

#define INFO(format, ...) log_logger_log(&logger, LOG_LOGLEVEL_INFO, format, ## __VA_ARGS__)
#define WARN(format, ...) log_logger_log(&logger, LOG_LOGLEVEL_WARNING, format, ## __VA_ARGS__)
#define ERRR(format, ...) do {log_logger_log(&logger, LOG_LOGLEVEL_ERROR, format, ## __VA_ARGS__); return -1;} while (0)

#define PARAM_INPUTELF 1
#define PARAM_OUTPUT 2

#define PARAMS_LEN 3

int main(int argc, char* argv[]) {
    log_logger_init(&logger, stdout);
    
    if (argc == 0)
        ERRR("Super error! How did this happen\n");

    if (argc != PARAMS_LEN)
        ERRR("Incorrect format! Format should be %s <inputelf> <outputfnk>\n", argv[0]);

    if (elf_version(EV_CURRENT) == EV_NONE)
        ERRR("Failed to initialize libelf\n");

    int ifile, ofile;
    if ((ifile = open(argv[PARAM_INPUTELF], O_RDONLY)) < 0)
        ERRR("Failed to open file %s\n", argv[PARAM_INPUTELF]);

    if ((ofile = open(argv[PARAM_INPUTELF], O_WRONLY)) < 0)
        ERRR("Failed to create fd to file %s\n", argv[PARAM_INPUTELF]);

    Elf* ielf;
    if (!(ielf = elf_begin(ifile, ELF_C_READ, NULL)) || elf_kind(ielf) != ELF_K_ELF)
        ERRR("Failed to make ELF handle\n");
    
    size_t shstrndx; // Who the hell named this??? It means section header string table index
    if (elf_getshdrstrndx(ielf, &shstrndx))
        ERRR("Failed to get section header string table index\n");

    INFO("Iterating over sections..\n");
    Elf_Scn* section = NULL;
    while ((section = elf_nextscn(ielf, section)) != NULL) {
        GElf_Shdr shdr;
        if (!gelf_getshdr(section, &shdr)) {
            WARN("Failed to get section header. Skipping\n");
            continue;
        }

        const char* name = elf_strptr(ielf, shstrndx, shdr.sh_name);
        INFO("Working on section %s with type %d\n", name, shdr.sh_type);
    }
    
    close(ifile);
    close(ofile);

    return 0;
}