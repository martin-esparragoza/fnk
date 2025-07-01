#ifndef LIB_UTIL_LINKHEADER_H_
#define LIB_UTIL_LINKHEADER_H_

typedef struct util_linkheader {
    const char* libname;
    void* methods[];
} util_linkheader_t;

#endif