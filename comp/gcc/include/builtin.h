/**
 * @brief Compiler-specific builtins
 * Another do-it-yourself file. Its expected that
 * - COMP_BUILTIN_ALLOCA(size)
 * be defined
 */

#ifndef COMP_INCLUDE_BUILTIN_H_
#define COMP_INCLUDE_BUILTIN_H_

#include "types.h"

#define COMP_BUILTIN_ALLOCA(size) __builtin_alloca(size)

#endif