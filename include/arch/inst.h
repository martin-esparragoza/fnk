/**
 * @file inst.h
 * Functions that need to be defined in assembly
 */
#pragma once

/**
 * Push all general registers onto the stack
 * And flags and allat
 */
void arch_inst_pusha();

/**
 * Pop all general registers onto the stack
 * And flags and allat
 */
void arch_inst_popa();

/**
 * First pushes ip onto the stack
 * Then moves current sp to where the parameter sp is pointing
 */
void arch_inst_enter(void* sp);

/**
 * Pretty much the inverse of the enter function.
 * sp points to -> sp register
 * Then pops ip off the stack in order to return control to the process
 */
void arch_inst_exit(void* sp);
