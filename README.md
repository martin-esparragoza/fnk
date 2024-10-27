An operating system frame. (written in C99 for GCC compiler)

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
    5. Load in librtfnk so it can also be linked as well as other libs
    6. Load in kernel and now execute it