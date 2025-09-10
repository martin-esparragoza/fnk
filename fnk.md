# Documentation for the FNK executable format

## Overview
The FNK executable format is an extremely simple format that
supports the creation of libraries, drivers, and general
programs. It supports dynamic linking with any program
(I will refer to all drivers, libraries, the kernel, and
general programs as programs from now on). Still, the format
requires that users do NOT utilize the data, bss, and other
sections due to the fact that supporting cross architecture
GOT data is a pain. Espescially when I'm targeting "light"
and old processors (like the 68000).

### Compilation flags
Here are some compilation flags for gcc that allow you to
generate your binary without it possibly breaking
`-fno-pic -fno-pie -fno-asynchronous-unwind-tables`
Inside your makefile make sure to add these to cflags and
ldflags

## Restrictions
Remember not to do anything stupid like try to use .so files
or something like that. Please be smart with it all. **All is
in the target endianness.**

## Recognized sections
Only a few specific sections are recognized and can be used in
a `.fnk` format. Those sections being:
* .ljd
* .text
* .pjd
* .data
* .rodata
* .bss (unincluded)

### Descriptor data (top)
This tells the operating system everything it needs to know
about if it needs to link, register or do anything like that
to your program. the following is in chronological order. All
of the following addresses are absolute (0 is 0 and relative
to the top)
| Parameter       | Size (bytes)                    | Value description                                                    |
| --------------- | ------------------------------- | -------------------------------------------------------------------- |
| MAGIC           | 6                               | 0xFE 0xED 'F' 'N' 'K' 'Y' - Used to confirm `.fnk` format.           |
| NAME            | 12                              | Name of your program. Must be unique.                                |
| RELOCATION-ADDR | ARCH_CONFIG_WORDSIZE (config.h) | Address to the relocation table (0 for none)                         |
| ENTRY-ADDR      | ARCH_CONFIG_WORDSIZE            | Address of the entry section (0 for none and therefore unexecutable) |
| LJD-ADDR        | ARCH_CONFIG_WORDSIZE            | Address of the LJD section                                           |
| PJD-ADDR        | ARCH_CONFIG_WORDSIZE            | Address of the PJD section                                           |
| BSS-LENGTH      | ARCH_CONFIG_WORDSIZE            | How long the blank storage section will be                           |

No LJD or PJD things relative data because they are already
exposed in a format we understand.

### Relocation table / unloaded runtime sections (chronologically after)
The actual relocation table is just directly placed here. It
is the only section that will be used only in load time
(instead of runtime). The format is as follows:
// TODO:
// REMEMBER TO INCLUDE A TERMINATION

### Unmapped and Loaded Sections (Chronologically after)
Unmapped sections like `.text` `.data` that are loaded (have
to do with runtime) are placed here. Sections like `.ljd` and
`.pjd` are all used during runtime so they will also be here.

#### .ljd (loaded)
Library jump descriptor section. This tells the operating
system where the functions you want to expose are. It is
simply defined as a list of addresses defined like so
```c
#include "mylibraryfunctions.h"
#include "attr.h"
#include "types.h"

COMP_ATTR__USED__ COMP_ATTR__SECTION__(".ljd") static uintptr_t ljd[] = {
   (uintptr_t) function_one,
   (uintptr_t) function_two,
   (uintptr_t) function_three
};
```
Do not touch during execution.

#### pjd (loaded)
Program jump descriptor. This is what your library must define
and other programs must include. A library must provide a
blank array of the **SAME SIZE** that will be copied over in
order to resolve the linking. Here is a sample pjd for the
previous ljd
```c
// mylibrarynamepjddef.h
// Remember to set your defines
#include "common/include/pjd.h"

COMP_ATTR__USED__ COMP_ATTR__SECTION__(".pjd") static struct common_pjd mylibraryname_pjd {
   .name = "mylibraryname"
};
```
With this, a memcpy will be done, moving the ljd to the pjd
before your program executes.Do not touch during execution.