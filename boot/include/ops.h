/**
 * @file ops.h
 * @brief Easy operations that you might need
 *
 * I think that "string.h" containing stuff like memcpy is BAD. If anything you can argue it should be in like mem or something.
 * BUT STRING IS FOR STRINGS.
 */

#ifndef LIB_UTIL_OPS_H_
#define LIB_UTIL_OPS_H_

#include "types.h"

bool util_ops_ispowertwo(unsigned x);

int util_ops_min(int a, int b);

int util_ops_max(int a, int b);

#endif