A simple operating system framework witten in C99

# About
This is a single threaded operating system frame with cooperative scheduling. It does not implement things such as memory protection or segmentation.
It is meant for things such as gaming consoles (or other devices with plug-and-play medias). Because of this libraries are strictly OS-packaged,
meaning that dynamic linkage is still possible, but only for OS packaged binaries. It has a microkernel and drivers are implemented through programs
and DLLs that interact with those programs. It is meant to be a heavily underprotected system.

### Note
* Currently this respository is configured for linux emulation, meaning that linkage and the whole shabang is broken and not happening

# Boot Process
1. User defined entry.o is where you start
    1. The goal of this process is to load in the bootloader
    2. Sections should also be set up
    3. It also must set up the heap
    4. Finally it will call main()
2. Bootloder
    1. Bootloader essentially just loads in the kernel (user configured static driver solely for kernel loading)
    2. 

A (SINGLE THREADED) operating system frame written in freestanding C99.

!CARE
* Unsafely written for the most part
* Designed to have an image file that fits in 4K of codespace
* CURRENTLY THIS REPOSITORY IS __CONFIGURED__ FOR EMULATION ON LINUX. THIS MEANS THAT THERE ARE SOME AREAS THAT ARE WRITTEN WITH A LOT OF DUCT TAPE (SEE FINAL COMPILATION STEPS). **TO MYSELF, PLEASE CLEAN UP THIS DUCT TAKE BEFORE RELEASING THIS OR SWITCHING TO A NEW EMULATION METHOD**

FEATURES (atttempted)
* Cooperative sceduling
* Socket API for communications (internally and externally)
* Dynamically allocated drivers that can be updated in real time
* Fast driver and interrupt processing
  
# "Documented" Boot Process
1. Begin in entry.o (src/entry/\{arch\}/entry.o can be generated however you want)
    1. Load in the bootloader (rest of linked binary file)
    2. Values such as the sp and mem_alloc_heap_start are set for use in the bootloader
    3. Call to main occours
2. main()
    1. Initialize PCB
    2. Load in dynamic linker.
    3. Link dynamic linker to the staying static drivers (static drivers in the staying section)
    4. Load in dynamically linked drivers
    5. Load in libfnk so it can also be linked as well as other libs
    6. Load in kernel and now execute it

## Posix deviations?
1. You shouldn't be trying to port code over usually. Its a HOBBY RTOS, most things should be custom
2. I disagree with some POSIX functions as they can be restrictive or hard to manage errors. I want error messages to be plentiful, easy to access, and give good information.

## User Defined Files
It is a frame so you do have to give it so elbow grease before it can run. (Remember that for the .h files make it so they can only be included once)
### `include/arch/$(ARCH)/config.h`
The following macros must be defined.
* `ARCH_CONFIG_VERBOSE 0-3`
    * 0 = No telemetry logs
    * 1 = Error logs only
    * 2 = Warning and error logs
    * 3 = Informational, warning, and error logs
* `ARCH_CONFIG_FAT16_SECTORBUFFER_SZ n` Number of sectors for the read buffer to read at a time in an operation (how much memory to allocate to internal FAT operations)
* `ARCH_CONFIG_FAT16_FAT n` FAT number to use as primary FAT
* `ARCH_CONFIG_FAT16_FATSZ n` How much memory to allocate for the FAT
### `include/arch/$(ARCH)/inst.h`
The following functions must be defined
`void arch_inst_popa()`
* Pops all general registers and flags off of the stack
`void arch_inst_enter(void* sp)`
* First pushes ip onto the stack then moves the sp register to where the parameter sp is pointing
`void arch_inst_exit(void* sp)`
* Moves what sp parameter points to to the sp register then pops ip off the stack
### `include/arch/$(ARCH)/types.h`
The following types must be defined
`uint8_t`  
`uint16_t`  
`uint32_t`  
`uint64_t`  
`int8_t`  
`int16_t`  
`int32_t`  
`int64_t`  
`uintmax_t`  
`intmax_t`  
`intptr_t`  
`uintptr_t`  
`size_t`  
`ssize_t`  
`bool`  
The following macros must be defined properly
`UINT8_WIDTH`  
`UINT16_WIDTH`  
`UINT32_WIDTH`  
`UINT64_WIDTH`  
`INT8_WIDTH`  
`INT16_WIDTH`  
`INT32_WIDTH`  
`INT64_WIDTH`  
`UINTMAX_WIDTH`  
`INTMAX_WIDTH`  
`SIZE_T_WIDTH`
`SSIZE_T_WIDTH`
`SIZE_MAX`
`SSIZE_MAX`
`true`  
`false`  
`NULL`  
### Optional weak method redefinitions
Commonly, a compiler can support built-in functions that utilize system architecture. While there are functions that will run fine freestanding, you might want to get a bit more performance by redefining these functions using builtins. The following functions can be redefined through any .c file inside of the `lib/comp/` directory
`void util_ops_bswap(void* data, size_t size)`  
`uint16_t util_ops_bswap16(uint16_t data)`  
`uint32_t util_ops_bswap32(uint32_t data)`  
`uint64_t util_ops_bswap64(uint64_t data)`  
`bool util_ops_ispowertwo(unsigned x)`  
`int util_ops_min(int a, int b)`  
`int util_ops_max(int a, int b)`  
`uintptr_t align(uintptr_t value, int toalign)`  
`void memcpy(void* dest, void* src, size_t length)`  
`void memset(void* dest, int val, size_t length)`  
`void memcmp(void* ptr0, void* ptr1, size_t length)`
### Static Drivers
All headers inside of the `include/sdrive/` directory must be satisfied in the `arch/$(ARCH)/` directory
### `include/comp/$(CC)`
The following macros for attributes must be satisfied
`COMP_ATTR__NORETURN__`  
`COMP_ATTR__USED__`  
`COMP_ATTR__ALIGNED__(n)`  
`COMP_ATTR__PACKED__`  
`COMP_ATTR__SECTION__(s)`  
`COMP_ATTR__NORETURN__`  
`COMP_ATTR__WEAK__`  

TODO (FIX) LIST:
- FAT16 Write
- FAT16 Allow for smaller than actual FAT size
- Telemetry actual error handling (error codes + error strings that are implemented in the .c file)

lib* directories will be preserved post-bootloader