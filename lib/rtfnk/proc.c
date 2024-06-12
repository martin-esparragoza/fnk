#include "../../include/rtfnk/proc.h"
#include "../../include/arch/inst.h"
#include "pcb.h"

inline void fnk_proc_yield(struct fnk_pcb* self) {
    arch_inst_pusha();
    fnk_proc_yieldnopreg(self);
}

inline void fnk_proc_yieldnopreg(struct fnk_pcb* self) {
    arch_inst_enter(self->stack);
}
