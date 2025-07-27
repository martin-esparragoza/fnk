#include "common/include/ops.h"
#include "types.h"
#include "attr.h"

bool COMP_ATTR__WEAK__ common_ops_ispowertwo(unsigned x) {
    return x && !(x & (x - 1));
}

int COMP_ATTR__WEAK__ common_ops_min(int a, int b) {
    return a > b ? b : a;
}

int COMP_ATTR__WEAK__ common_ops_max(int a, int b) {
    return a > b ? a : b;
}