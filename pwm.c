/******************************************************************************************
*
*   MODULE:
*       pwm.c
*
*   DESCRIPTION:
*       This file includes PWM related procedures.
*
*   Created by Seongkwan Lee on Oct 27, 2020
*
******************************************************************************************/

/*-----------------------------------------------------------------------------------------
                                     GENERAL INCLUDES
-----------------------------------------------------------------------------------------*/

#include "pwm.h"

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
                                     MEMORY CONSTANTS
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
                                        VARIABLES
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
                                       PROCEDURES
-----------------------------------------------------------------------------------------*/


/********************************************************************
*
*   PROCEDURE NAME:
*       pwm_1_2_init
*
*   DESCRIPTION:
*       Initialize PWM 1 and 2.
*
********************************************************************/

void pwm_1_2_init
    (
    uint16_t period,
    uint16_t duty1,
    uint16_t duty2
    )
{
/**********************************************************
Bad inputs
**********************************************************/
if( ( duty1 >= period )
 || ( duty2 >= period ) )
    {
    return;
    }

/**********************************************************
PWM outputs on P2.4, P2.5
SMCLK = 48MHz/4 = 12 MHz, 83.33ns
Counter counts up to TA0CCR0 and back down
Let Timerclock period T = 8/12MHz = 666.7ns
P2.4=1 when timer equals TA0CCR1 on way down
P2.4=0 when timer equals TA0CCR1 on way up
P2.5=1 when timer equals TA0CCR2 on way down
P2.5=0 when timer equals TA0CCR2 on way up
Period of P2.4 is period*1.333us, duty cycle is duty1/period
Period of P2.5 is period*1.333us, duty cycle is duty2/period
**********************************************************/
P2->DIR |= 0x30;            // P2.4, P2.5 output
P2->SEL0 |= 0x30;           // P2.4, P2.5 Timer0A functions
P2->SEL1 &= ~0x30;          // P2.4, P2.5 Timer0A functions
TIMER_A0->CCTL[0] = 0x0080; // CCI0 toggle
TIMER_A0->CCR[0] = period;  // Period is 2*period*8*83.33ns is 1.333*period
TIMER_A0->EX0 = 0x0000;     //    divide by 1
TIMER_A0->CCTL[1] = 0x0040; // CCR1 toggle/reset
TIMER_A0->CCR[1] = duty1;   // CCR1 duty cycle is duty1/period
TIMER_A0->CCTL[2] = 0x0040; // CCR2 toggle/reset
TIMER_A0->CCR[2] = duty2;   // CCR2 duty cycle is duty2/period
TIMER_A0->CTL = 0x02F0;     // SMCLK=12MHz, divide by 8, up-down mode
// bit  mode
// 9-8  10    TASSEL, SMCLK=12MHz
// 7-6  11    ID, divide by 8
// 5-4  11    MC, up-down mode
// 2    0     TACLR, no clear
// 1    0     TAIE, no interrupt
// 0          TAIFG
}   /* pwm_1_2_init() */


//***************************PWM_Duty1*******************************
// change duty cycle of PWM output on P2.4
// Inputs:  duty1
// Outputs: none
// period of P2.4 is 2*period*666.7ns, duty cycle is duty1/period
void pwm_1_duty
    (
    uint16_t duty1
    )
{
/**********************************************************
Bad inputs
**********************************************************/
if( duty1 >= TIMER_A0->CCR[0] )
    {
    return;
    }
/**********************************************************
CCR1 duty cycle is duty1/period
**********************************************************/
TIMER_A0->CCR[1] = duty1;
}   /* pwm_1_duty() */


//***************************PWM_Duty2*******************************
// change duty cycle of PWM output on P2.5
// Inputs:  duty2
// Outputs: none// period of P2.5 is 2*period*666.7ns, duty cycle is duty2/period
void pwm_2_duty
    (
    uint16_t duty2
    )
{
/**********************************************************
Bad inputs
**********************************************************/
if( duty2 >= TIMER_A0->CCR[0] )
    {
    return;
    }

/**********************************************************
CCR2 duty cycle is duty2/period
**********************************************************/
TIMER_A0->CCR[2] = duty2;
}


//***************************PWM_Init34*******************************
// PWM outputs on P2.6, P2.7
// Inputs:  period (1.333us)
//          duty3
//          duty4
// Outputs: none
// SMCLK = 48MHz/4 = 12 MHz, 83.33ns
// Counter counts up to TA0CCR0 and back down
// Let Timerclock period T = 8/12MHz = 666.7ns
// period of P7.3 squarewave is 4*period*666.7ns
// P2.6=1 when timer equals TA0CCR3 on way down, P2.6=0 when timer equals TA0CCR3 on way up
// P2.7=1 when timer equals TA0CCR4 on way down, P2.7=0 when timer equals TA0CCR4 on way up
// Period of P2.6 is period*1.333us, duty cycle is duty3/period
// Period of P2.7 is period*1.333us, duty cycle is duty4/period

/********************************************************************
*
*   PROCEDURE NAME:
*       pwm_3_4_init
*
*   DESCRIPTION:
*       Initialize PWM 3 and 4.
*
********************************************************************/

void pwm_3_4_init
    (
    uint16_t period,
    uint16_t duty3,
    uint16_t duty4
    )
{
// bad input
if( ( duty3 >= period )
 || ( duty4 >= period ) )
    {
    return;
    }

P2->DIR |= 0xC0;          // P2.6, P2.7 output
P2->SEL0 |= 0xC0;         // P2.6, P2.7 Timer0A functions
P2->SEL1 &= ~0xC0;        // P2.6, P2.7 Timer0A functions
TIMER_A0->CCTL[0] = 0x0080;      // CCI0 toggle
TIMER_A0->CCR[0] = period;       // Period is 2*period*8*83.33ns is 1.333*period
TIMER_A0->EX0 = 0x0000;        //    divide by 1
TIMER_A0->CCTL[3] = 0x0040;      // CCR3 toggle/reset
TIMER_A0->CCR[3] = duty3;        // CCR3 duty cycle is duty1/period
TIMER_A0->CCTL[4] = 0x0040;      // CCR4 toggle/reset
TIMER_A0->CCR[4] = duty4;        // CCR4 duty cycle is duty2/period
TIMER_A0->CTL = 0x02F0;        // SMCLK=12MHz, divide by 8, up-down mode
// bit  mode
// 9-8  10    TASSEL, SMCLK=12MHz
// 7-6  11    ID, divide by 8
// 5-4  11    MC, up-down mode
// 2    0     TACLR, no clear
// 1    0     TAIE, no interrupt
// 0          TAIFG

}   /* pwm_3_4_init() */


//***************************PWM_Duty3*******************************
// change duty cycle of PWM output on P2.6
// Inputs:  duty3
// Outputs: none
// period of P2.6 is 2*period*666.7ns, duty cycle is duty3/period
void pwm_3_duty
    (
    uint16_t duty3
    )
{
// bad input
if( duty3 >= TIMER_A0->CCR[0] )
    {
    return;
    }
TIMER_A0->CCR[3] = duty3;        // CCR3 duty cycle is duty1/period
}


//***************************PWM_Duty4*******************************
// change duty cycle of PWM output on P2.7
// Inputs:  duty4
// Outputs: none// period of P2.7 is 2*period*666.7ns, duty cycle is duty2/period
void pwm_4_duty
    (
    uint16_t duty4
    )
{
// bad input
if( duty4 >= TIMER_A0->CCR[0] )
      {
      return;
      }
TIMER_A0->CCR[4] = duty4;        // CCR4 duty cycle is duty1/period
}


//***************************PWM_RobotArmInit*******************************
// PWM outputs on P2.4/PM_TA0.1 (PMAP from TA1.1), P3.5/PM_UCB2CLK (PMAP from TA1.2), and P5.7/TA2.2/VREF-/VeREF-/C1.6
// Inputs:  period (333.33ns)
//          duty0 (0<=duty0<period-1)
//          duty1 (0<=duty1<period-1)
//          duty2 (0<=duty2<period-1)
// Outputs: none
// SMCLK = 48MHz/4 = 12 MHz, 83.33ns
// Use clock divider of 2 to get timer clock period 166.67ns
// Counter counts up to TAnCCR0 and back down
// Let Timerclock period T = 2/12MHz = 166.67nsns
// P2.4=1 when timer equals TA1CCR1 on way down, P2.4=0 when timer equals TA1CCR1 on way up
// P3.5=1 when timer equals TA1CCR2 on way down, P3.5=0 when timer equals TA1CCR2 on way up
// P5.7=1 when timer equals TA2CCR2 on way down, P5.7=0 when timer equals TA2CCR2 on way up
// Period of P2.4 is period*333.33ns, duty cycle is duty0/period
// Period of P3.5 is period*333.33ns, duty cycle is duty1/period
// Period of P5.7 is period*333.33ns, duty cycle is duty2/period
void pwm_robot_arm_init
    (
    uint16_t period,
    uint16_t duty0,
    uint16_t duty1,
    uint16_t duty2
    )
{
// bad input
if( ( duty0 >= period )
 || ( duty1 >= period )
 || ( duty2 >= period ) )
    {
    return;
    }

TIMER_A1->CTL &= ~0x0030;      // halt TimerA1 while port mapping is in progress
PMAP->KEYID = 0x2D52;          // write key to unlock write access to PMAP registers
PMAP->CTL = 0x0002;            // allow reconfiguration of port mapping (in case needed in another module)
P2MAP->PMAP_REGISTER4 = PMAP_TA1CCR1A;// configure P2.4 as TA1.1
P2->DIR |= 0x10;               // P2.4 output
P2->SEL0 |= 0x10;              // P2.4 PMAP functions
P2->SEL1 &= ~0x10;             // P2.4 PMAP functions
P3MAP->PMAP_REGISTER5 = PMAP_TA1CCR2A;// configure P3.5 as TA1.2
P3->DIR |= 0x20;               // P3.5 output
P3->SEL0 |= 0x20;              // P3.5 PMAP functions
P3->SEL1 &= ~0x20;             // P3.5 PMAP functions
PMAP->KEYID = 0x0000;          // write incorrect key to lock write access to PMAP registers
TIMER_A1->CCTL[0] = 0x0080;    // CCI0 toggle
TIMER_A1->CCR[0] = period - 1; // Period is 2*period*8*166.67ns is 2.666*period
TIMER_A1->EX0 = 0x0000;        //    divide by 1
TIMER_A1->CCTL[1] = 0x0040;    // CCR1 toggle/reset
TIMER_A1->CCR[1] = duty0;      // CCR1 duty cycle is duty0/period
TIMER_A1->CCTL[2] = 0x0040;    // CCR2 toggle/reset
TIMER_A1->CCR[2] = duty1;      // CCR2 duty cycle is duty1/period
TIMER_A1->CTL = 0x0270;        // SMCLK=12MHz, divide by 2, up-down mode
// bit  mode
// 9-8  10    TASSEL, SMCLK=12MHz
// 7-6  01    ID, divide by 2
// 5-4  11    MC, up-down mode
// 2    0     TACLR, no clear
// 1    0     TAIE, no interrupt
// 0          TAIFG
P5->DIR |= 0x80;               // P5.7 output
P5->SEL0 |= 0x80;              // P5.7 TimerA2.2 functions
P5->SEL1 &= ~0x80;             // P5.7 TimerA2.2 functions
TIMER_A2->CCTL[0] = 0x0080;    // CCI0 toggle
TIMER_A2->CCR[0] = period - 1; // Period is 2*period*8*166.67ns is 2.666*period
TIMER_A2->EX0 = 0x0000;        //    divide by 1
TIMER_A2->CCTL[2] = 0x0040;    // CCR2 toggle/reset
TIMER_A2->CCR[2] = duty2;      // CCR2 duty cycle is duty2/period
TIMER_A2->CTL = 0x0270;        // SMCLK=12MHz, divide by 2, up-down mode
// bit  mode
// 9-8  10    TASSEL, SMCLK=12MHz
// 7-6  01    ID, divide by 2
// 5-4  11    MC, up-down mode
// 2    0     TACLR, no clear
// 1    0     TAIE, no interrupt
// 0          TAIFG
}


//***************************PWM_RobotArmDuty0*******************************
// change duty cycle of PWM output on P2.4
// Inputs:  duty0
// Outputs: none
// Period of P2.4 is period*333.33ns, duty cycle is duty0/period
void pwm_robot_arm_0_duty
    (
    uint16_t duty0
    )
{
if( duty0 >= TIMER_A1->CCR[0] )
    {
    return; // bad input
    }

TIMER_A1->CCR[1] = duty0;      // CCR1 duty cycle is duty0/period
}


//***************************PWM_RobotArmGetDuty0*******************************
// get the duty cycle of PWM output on P2.4
// Inputs: none
// Outputs: duty0
// Period of P2.4 is period*333.33ns, duty cycle is duty0/period
uint16_t pwm_robot_arm_get_0_duty
    (
    void
    )
{
return TIMER_A1->CCR[1];       // CCR1 duty cycle is duty0/period
}


//***************************PWM_RobotArmDuty1*******************************
// change duty cycle of PWM output on P3.5
// Inputs:  duty1
// Outputs: none
// Period of P3.5 is period*333.33ns, duty cycle is duty1/period
void pwm_robot_arm_1_duty
    (
    uint16_t duty1
    )
{
if( duty1 >= TIMER_A1->CCR[0] )
    {
    return; // bad input
    }

TIMER_A1->CCR[2] = duty1;      // CCR2 duty cycle is duty1/period
}


//***************************PWM_RobotArmGetDuty1*******************************
// get the duty cycle of PWM output on P3.5
// Inputs: none
// Outputs: duty1
// Period of P3.5 is period*333.33ns, duty cycle is duty1/period
uint16_t pwm_robot_arm_get_1_duty
    (
    void
    )
{
return TIMER_A1->CCR[2];       // CCR2 duty cycle is duty1/period
}


//***************************PWM_RobotArmDuty2*******************************
// change duty cycle of PWM output on P5.7
// Inputs:  duty2
// Outputs: none
// Period of P5.7 is period*333.33ns, duty cycle is duty2/period
void pwm_robot_arm_2_duty
    (
    uint16_t duty2
    )
{
if( duty2 >= TIMER_A2->CCR[0] )
    {
    return; // bad input
    }

TIMER_A2->CCR[2] = duty2;      // CCR2 duty cycle is duty2/period
}


//***************************PWM_RobotArmGetDuty2*******************************
// get the duty cycle of PWM output on P5.7
// Inputs: none
// Outputs: duty2
// Period of P5.7 is period*333.33ns, duty cycle is duty2/period
uint16_t pwm_robot_arm_get_2_duty
    (
    void
    )
{
return TIMER_A2->CCR[2];       // CCR2 duty cycle is duty2/period
}

