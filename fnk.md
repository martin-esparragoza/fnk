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

## Restrictions
You may NOT use the `.data` `.rodata` `.bss` or any other
sections besides `.entry` and .`text` during program
execution. This is because we cannot afford to deal with
absolute addressing. To verify that the program you wrote is
valid and will not have errors PLEASE compile to .elf or
something like that and do an objdump. The objdump will reveal
if your program is attempting to create things in sections
it shouldn't be. **YOU HAVE TO USE THE SAME COMPILATION FLAGS
JUST NOT THE LINKER** If you must create global variables and
constants, please use the `COMP_ATTR__SECTION__(".text")`
from `"alloc.h"` to specify to the compiler that your constant
is allocated there. **All is in the target endianness.**

### .desc
The descriptor data of your program. This tells the operating
system everything it needs to know about if it needs to link,
register or do anything like that to your program. the
following is in chronological order.
| Parameter | Size (bytes)                     | Value description                                                          |
| --------- | -------------------------------- | -------------------------------------------------------------------------- |
| MAGIC     | 2                                | 0xFEED - Used to confirm `.fnk` format.                                    |
| NAME      | 12 (also defined in fnkconfig.h) | Name of your program. Must be unique. Remember to null terminate.          |
| MAIN-ADDR | uintptr_t                        | Address of main function. NULL for no program execution.                   |
| LJD-ADDR  | uintptr_t                        | Address of the library jump descriptor section. NULL for exposing nothing. |
| PJDS-ADDR | uintptr_t                        | Address of the program jump descritpr. NULL for requiring nothing.         |
| SIZE      | uint32_t                         | Size of the entire binary                                                  |

Do not touch during exection.

### ljd
Library jump descriptor section. This tells the operating
system where the functions you want to expose are. It is
simply defined as a list of addresses defined like so
```c
#include "mylibraryfunctions.h"
#include "attr.h"
#include "types.h"

COMP_ATTR__SECTION__(".text") static uintptr_t ljd[] = {
   (uintptr_t) function_one,
   (uintptr_t) function_two,
   (uintptr_t) function_three
};
```
Do not touch during execution.

### pjds
Program jump descriptor. This is what your library must define
and other programs must include. A library must provide a
blank array of the **SAME SIZE** that will be copied over in
order to resolve the linking. Here is a sample pjd for the
previous ljd
```c
// mylibrarynamepjddef.h
{
   .name = "mylibraryname"
};
```
```c
// programthatwantstoincludethis.c
#include "common/include/pjd.h"
#include "attr.h"

COMP_ATTR__SECTION__(".text") static struct pjd pjds[] = {
   #include "mylibrarynamepjddef.h" ,
   #include "myotherlibrarynamepjddef.h"
};
```
With this, a memcpy will be done, moving the ljd to the pjd
before your program executes. This must be in `.text` to
encourage the program to not use absolute addressing. Do not
touch during execution.