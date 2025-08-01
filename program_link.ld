/* All programs will be converted to the executable format through the following linker script */
WORDSIZE = 16 /* Define this to your desired word size */

OUTPUT_FORMAT(binary);

SECTIONS {
    .progh : ALIGN(WORDSIZE) {
        KEEP(*( .progh ));
    }

    /* Library jump table */
    .ljt : ALIGN(WORDSIZE) {
        KEEP(*( .ljt ));
    }

    /* Program jump table */
    .pjt : ALIGN(WORDSIZE) {
        KEEP(*( .pjt ));
    }

    .text : ALIGN(WORDSIZE) {
        __linker_text_start = .;
        *( .entry ); /* We have to place this at the top of the thing. There should only be one function here */
        *( .text .text.* );
        __linker_text_end = .;
    }

    .rodata : ALIGN(WORDSIZE) {
        __linker_rodata_start = .;
        *( .rodata .rodata.* );
        __linker_rodata_end = .;
    }

    .data : ALIGN(WORDSIZE) {
        __linker_data_start = .;
        *( .data .data.* );
        __linker_data_end = .;
    }

    .bss : ALIGN(WORDSIZE) {
        __linker_bss_start = .;
        *( .bss .bss.* COMMON );
        __linker_bss_end = .;
    }
}