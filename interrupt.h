#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <stdint.h>

/**
 * Disables Interrupts
 *
 * @param  none
 * @return none
 *
 * @brief  Sets the I bit in the PRIMASK to disable interrupts.
 */
void interrupt_disable
    (
    void
    );


/**
 * Enables Interrupts
 *
 * @param  none
 * @return none
 *
 * @brief  clears the I bit in the PRIMASK to enable interrupts
 */
void interrupt_enable
    (
    void
    );


/**
 * Start a critical section. Code between StartCritical and EndCritical is run atomically
 *
 * @param  none
 * @return copy of the PRIMASK (I bit) before StartCritical called
 *
 * @brief  Saves a copy of PRIMASK and disables interrupts
 */
void interrupt_start_critical
    (
    void
    );


/**
 * End a critical section. Code between StartCritical and EndCritical is run atomically
 *
 * @param  sr is PRIMASK (I bit) before StartCritical called
 * @return none
 *
 * @brief  Sets PRIMASK with value passed in
 */
void interrupt_end_critical
    (
    void
    );


/**
 * Enters low power sleep mode waiting for interrupt (WFI instruction)
 * processor sleeps until next hardware interrupt
 * returns after ISR has been run
 *
 * @param  none
 * @return none
 *
 * @brief  Enters low power sleep mode waiting for interrupt
 */
void interrupt_wait_for_interrupt
    (
    void
    );


#endif /* INTERRUPT_H_ */
