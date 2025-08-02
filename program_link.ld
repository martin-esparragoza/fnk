/* All programs will be converted to the executable format through the following linker script */
WORDSIZE = 16 /* Define this to your desired word size */

OUTPUT_FORMAT(binary);

SECTIONS {
    .desc : ALIGN(WORDSIZE) {
        KEEP(*( .desc ));
    }

    /* Library jump descriptor */
    .ljd : ALIGN(WORDSIZE) {
        KEEP(*( .ljd ));
    }

    .text : ALIGN(WORDSIZE) {
        __linker_text_start = .;
        *( .text .text.* );
        __linker_text_end = .;
    }
    
    /**
     * Yes, we did discard .data, .rodata, .bss . This is because GCC is very
     * happy to use absolute addressing on these sections and we can't support
     * that without doing different things for different architectures.
     * I don't want to write a giant dynamic linker so because of that we're just
     * going to attempt to put everything inside of .text and the rest will be
     * dynamically allocated. Yes, it sucks. Also, you should probably compile
     * the object file for yourself as something that isnt .fnk so you can check
     * if gcc is going to generate something in a section you don't want it to.
     */
}