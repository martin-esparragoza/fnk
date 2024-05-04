/**
 * @file pcb.h
 * @brief Process Control Block
 */

#ifndef INCLUDE_RTFNK_PCB_H_
#define INCLUDE_RTFNK_PCB_H_

/**
 * PCB
 * Process
 * Control
 * Block
 */
typedef struct fnk_pcb {
    void* stack; ///< Pointer to the stack in order to yield control
} fnk_pcb_t;

#endif
