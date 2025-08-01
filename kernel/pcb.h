/**
 * @file pcb.h
 * @brief Process control block
 */

#ifndef LIB_FNK_PCB_H_
#define LIB_FNK_PCB_H_

#include "include/fnk/pcb.h"

struct fnk_pcb {
    void* stack; ///< Pointer to the stack in order to yield control
};

#endif