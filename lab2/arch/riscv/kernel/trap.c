#include "trap.h"
#include "types.h"
#include "clock.h"
#include "printk.h"

void handler_interrupt(uint64 scause, uint64 sepc, uint64 regs) {
    switch (scause & ~TRAP_MASK) {
        case STI:
            printk("[S] Supervisor Mode Timer Interrupt\n");
            clock_set_next_event();
            break;
        default:
            break;
    }
    printk("kernel is running!\n");
}

void handler_exception(uint64 scause, uint64 sepc, uint64 regs) {
}

void trap_handler(uint64 scause, uint64 sepc, uint64 regs) {
    if (scause & TRAP_MASK)                    // #define TRAP_MASK (1UL << 63)
        handler_interrupt(scause, sepc, regs);
    else
        handler_exception(scause, sepc, regs);
}
