/**
 * @file inst.h
 * Functions that need to be defined in assembly
 */

#ifndef BOOT_INCLUDE_ARCH_INST_H_
#define BOOT_INCLUDE_ARCH_INST_H_

/**
 * Push all general registers onto the stack
 * And flags and allat
 */
void arch_inst_pusha() {;}

/**
 * Pop all general registers onto the stack
 * And flags and allat
 */
void arch_inst_popa() {;}

/**
 * First pushes ip onto the stack
 * Then moves current sp to where the parameter sp is pointing
 */
void arch_inst_enter(const void* sp) {;}

/**
 * Pretty much the inverse of the enter function.
 * sp points to -> sp register
 * Then pops ip off the stack in order to return control to the process
 */
void arch_inst_exit(const void* sp) {;}

#endif
