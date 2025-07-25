/**
 * @file proc.h
 * @brief Processes use this to interface with the process system
 */
#ifndef INCLUDE_RTFNK_PROCF_H
#define INCLUDE_RTFNK_PROCF_H

struct fnk_proc;
typedef struct fnk_proc fnk_proc_t;

/**
 * @brief Yield
 * Executed directly.
 * Relinquishes control of quantum
 * If you call this with not yourself... what are you doing first of all?? But it will have undefined behavior.
 */
void fnk_proc_yield(struct fnk_proc* process);

/**
 * @brief Yield w/o register perserve
 * Yield the program and don't perserve registers
 * Only do this if you really know what youre doing...
 * If you call this with not yourself... what are you doing first of all?? But it will have undefined behavior.
 */
void fnk_proc_yieldnopreg(struct fnk_proc* process);

#endif
