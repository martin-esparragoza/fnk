/**
 * @file inst.h
 * @brief Functions that need to be defined in assembly
 */

#ifndef ARCH_INCLUDE_INST_H_
#define ARCH_INCLUDE_INST_H_

/**
 * @brief Push all general registers onto the stack
 */
void arch_inst_pusha(void) {;}

/**
 * @brief Pop all general registers onto the stack
 */
void arch_inst_popa(void) {;}

/**
 * @brief Push ip to stack and move sp when the parameter sp is pointing
 */
void arch_inst_enter(const void* sp) {;}

/**
 * @brief Inverse of enter.
 */
void arch_inst_exit(const void* sp) {;}

#endif
