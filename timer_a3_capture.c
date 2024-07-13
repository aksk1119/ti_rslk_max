/******************************************************************************************
*
*   MODULE:
*       timer_a3_capture.c
*
*   DESCRIPTION:
*       This file includes Timer A3 related procedures.
*
*   Created by Seongkwan Lee on Oct 27, 2020
*
******************************************************************************************/


/*-----------------------------------------------------------------------------------------
                                     GENERAL INCLUDES
-----------------------------------------------------------------------------------------*/

#include <stdint.h>

#include "interrupt.h"
#include "util.h"
#include "timer_a3_capture.h"

/*-----------------------------------------------------------------------------------------
                                  DESIGN ASSURANCE LEVEL
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
                                         MACROS
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
                                    LITERAL CONSTANTS
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
                                         TYPES
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
                                     PROJECT INCLUDES
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
                                     MEMORY CONSTANTS
-----------------------------------------------------------------------------------------*/

void timer_a3_empty_function( uint16_t t ){};

/*-----------------------------------------------------------------------------------------
                                        VARIABLES
-----------------------------------------------------------------------------------------*/

void ( *capture_task0 )( uint16_t time ) = timer_a3_empty_function;
void ( *capture_task1 )( uint16_t time ) = timer_a3_empty_function;

/*-----------------------------------------------------------------------------------------
                                       PROCEDURES
-----------------------------------------------------------------------------------------*/



/********************************************************************
*
*   PROCEDURE NAME:
*       timer_a3_capture_register_callback
*
*   DESCRIPTION:
*       Initialize Timer A3 in edge time mode to request interrupts
*       on the rising edges of P10.4 (TA3CCP0) and P10.5 (TA3CCP1).
*       The interrupt service routines acknowledge the interrupt and
*       call a user function.
*
*   NOTE:
*       Assumes low-speed subsystem master clock is 12 MHz
*
********************************************************************/

void timer_a3_capture_register_callback
    (
    void( *task0 )( uint16_t time ),
    void( *task1 )( uint16_t time )
    )
{
capture_task0 = task0;
capture_task1 = task1;

TIMER_A3->CTL &= ~0x0030;
TIMER_A3->CTL = 0x0200;

TIMER_A3->CCTL[0] = 0x4910;
TIMER_A3->CCTL[1] = 0x4910;
TIMER_A3->EX0 &= ~0x0007;
NVIC->IP[2] = ( NVIC->IP[2] & 0xFFFFFF00 ) | 0x00000040;
NVIC->ISER[0] = 0x00000100;
NVIC->IP[2] = ( NVIC->IP[2] & 0x00FFFFFF ) | 0x40000000;
NVIC->ISER[0] = 0x00000200;
TIMER_A3->CTL |= 0x0024;

}   /* timer_a3_capture_register_callback() */


/********************************************************************
*
*   PROCEDURE NAME:
*       TA3_0_IRQHandler
*
*   DESCRIPTION:
*       Timer A3 interrupt request handler.
*
********************************************************************/

void TA3_0_IRQHandler
    (
    void
    )
{
// write this for Lab 16
TIMER_A3->CCTL[0] &= ~0x0001;
( *capture_task0 )( TIMER_A3->CCR[0] );

}   /* TA3_0_IRQHandler() */


/********************************************************************
*
*   PROCEDURE NAME:
*       TA3_N_IRQHandler
*
*   DESCRIPTION:
*       Timer A3 interrupt request handler.
*
********************************************************************/

void TA3_N_IRQHandler
    (
    void
    )
{
// write this for Lab 16
TIMER_A3->CCTL[1] &= ~0x0001;
( *capture_task1 )( TIMER_A3->CCR[1] );

}   /* TA3_N_IRQHandler() */
