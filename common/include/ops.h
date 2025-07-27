/**
 * @file ops.h
 * @brief Easy operations that you might need
 *
 * I think that "string.h" containing stuff like memcpy is BAD. If anything you can argue it should be in like mem or something.
 * BUT STRING IS FOR STRINGS.
 */

#ifndef COMMON_INCLUDE_OPS_H_
#define COMMON_INCLUDE_OPS_H_

#include "types.h"

bool common_ops_ispowertwo(unsigned x);

int common_ops_min(int a, int b);

int common_ops_max(int a, int b);

#endif