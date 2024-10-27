ENTRY(entry);
WORDSIZE = 8; /* bytes */

SECTIONS {
    .text : ALIGN(WORDSIZE) {
        __linker_text_start = .;
        *( .text );
        __linker_text_end = .;
    }
    
    .data : ALIGN(WORDSIZE) {
        __linker_data_start = .;
        *( .data );
        __linker_data_end = .;
    }

    .memdump : ALIGN(WORDSIZE) {
        __linker_memdump_start = .;
        *( .memdump );
        __linker_memdump_end = .;
    }
    
    .bss : ALIGN(WORDSIZE) {
        __linker_bss_start = .;
        *( .bss );
        __linker_bss_end = .;
    }
}