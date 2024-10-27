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