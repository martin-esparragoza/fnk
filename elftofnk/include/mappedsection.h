#ifndef ELFTOFNK_INCLUDE_MAPPEDSECTION_H_
#define ELFTOFNK_INCLUDE_MAPPEDSECTION_H_

#include <bfd.h>
#include <stdbool.h>

// Just a nice way to group everything together and target things through mapping
typedef struct elftofnk_mappedsection {
    const char* name;
    asection* section;
    arelent** reloctable;
    long numrelocentries;
    void* data;
    bool required;
} elftofnk_mappedsection_t;

#endif