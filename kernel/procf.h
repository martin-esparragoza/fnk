/**
 * @file procf.h
 * @brief Process system functions
 */
#ifndef DLL_FNK_INCLUDE_PROC_H_
#define DLL_FNK_INCLUDE_PROC_H_

/**
 * @brief Yield
 * @note Preserves registers by pushing them onto the stack
 * @param [in] process Must be your own process
 */
void fnk_proc_yield(struct fnk_proc* process);

/**
 * @brief Yield w/o register perserve
 * @param [in] process Must be your own process
 */
void fnk_proc_yieldnopreg(struct fnk_proc* process);

#endif
