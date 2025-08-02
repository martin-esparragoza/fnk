/* All programs will be converted to the executable format through the following linker script */
WORDSIZE = 16 /* Define this to your desired word size */

OUTPUT_FORMAT(binary);

SECTIONS {
    .desc : ALIGN(WORDSIZE) {
        __linker_desc_start = .;
        KEEP(*( .desc ));
        __linker_desc_end = .;
    }

    /* Library jump descriptor */
    .ljd : ALIGN(WORDSIZE) {
        __linker_ljd_start = .;
        KEEP(*( .ljd ));
        __linker_ljd_end = .;
    }

    .text : ALIGN(WORDSIZE) {
        __linker_text_start = .;
        *( .text* );
        __linker_text_end = .;

        __linker_data_start = .;
        *( .data* );
        __linker_data_end = .;
        
        __linker_rodata_start = .;
        *( .rodata* );
        __linker_rodata_end = .;

        __linker_pjds_start = .;
        *( .pjds );
        __linker_pjds_end = .;
        
        __linker_bss_start = .;
        *( .bss* );
        __linker_bss_end = .;
    }
}