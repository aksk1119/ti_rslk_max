#include <stdint.h>
#include "interrupt.h"


//*********** DisableInterrupts ***************
// disable interrupts
// inputs:  none
// outputs: none
void interrupt_disable
    (
    void
    )
{
__asm ("    CPSID  I\n"
       "    BX     LR\n");
}


//*********** EnableInterrupts ***************
// enable interrupts
// inputs:  none
// outputs: none
void interrupt_enable
    (
    void
    )
{
__asm  ("    CPSIE  I\n"
        "    BX     LR\n");
}


//*********** StartCritical ************************
// make a copy of previous I bit, disable interrupts
// inputs:  none
// outputs: previous I bit
void interrupt_start_critical
    (
    void
    )
{
__asm  ("    MRS    R0, PRIMASK   ; save old status \n"
        "    CPSID  I             ; mask all (except faults)\n"
        "    BX     LR\n");
}


//*********** EndCritical ************************
// using the copy of previous I bit, restore I bit to previous value
// inputs:  previous I bit
// outputs: none
void interrupt_end_critical
    (
    void
    )
{
__asm  ("    MSR    PRIMASK, R0\n"
        "    BX     LR\n");
}


//*********** WaitForInterrupt ************************
// go to low power mode while waiting for the next interrupt
// inputs:  none
// outputs: none
void interrupt_wait_for_interrupt
    (
    void
    )
{
__asm  ("    WFI\n"
        "    BX     LR\n");
}
