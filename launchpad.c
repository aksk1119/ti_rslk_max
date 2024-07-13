// built-in LED1 connected to P1.0
// negative logic built-in Button 1 connected to P1.1
// negative logic built-in Button 2 connected to P1.4
// built-in red LED connected to P2.0
// built-in green LED connected to P2.1
// built-in blue LED connected to P2.2

#include "launchpad.h"


//------------LaunchPad_Init------------
// Initialize Switch input and LED output
// Input: none
// Output: none
void launchpad_init
    (
    void
    )
{
P1->SEL0 &= ~0x13;
P1->SEL1 &= ~0x13;     // 1) configure P1.4, P1.1, and P1.0 as GPIO
P1->DIR  &= ~0x12;     // 2) make P1.4 and P1.1 in
P1->DIR  |= 0x01;      //    make P1.0 out
P1->REN  |= 0x12;      // 3) enable pull resistors on P1.4 and P1.1
P1->OUT  |= 0x12;      //    P1.4 and P1.1 are pull-up
P2->SEL0 &= ~0x07;
P2->SEL1 &= ~0x07;     // 1) configure P2.2-P2.0 as GPIO
P2->DIR  |= 0x07;      // 2) make P2.2-P2.0 out
P2->DS   |= 0x07;      // 3) activate increased drive strength
P2->OUT  &= ~0x07;     //    all LEDs off
}


//------------LaunchPad_Input------------
// Input from Switches
// Input: none
// Output: 0x00 none
//         0x01 Button1
//         0x02 Button2
//         0x03 both Button1 and Button2
uint8_t launchpad_buttons_read
    (
    void
    )
{
// read P1.4,P1.1 inputs
return( ( ( ( ~( P1->IN ) ) & 0x10 ) >> 3 ) | ( ( ( ~( P1->IN ) ) & 0x02 ) >> 1 ) );
}


//------------LaunchPad_LED------------
// Output to LaunchPad red LED
// Input: 0 off, 1 on
// Output: none
void launchpad_led_ctrl
    (
    uint8_t data
    )
{
// write one bit to P1.0
P1->OUT = ( ( P1->OUT & 0xFE ) | data );
}


//------------LaunchPad_Output------------
// Output to LaunchPad LEDs
// Input: 0 off, bit0=red,bit1=green,bit2=blue
// Output: none
void launchpad_3_color_led_ctrl
    (
    uint8_t data
    )
{
// write three outputs bits of P2
P2->OUT = ( ( P2->OUT & 0xF8 ) | ( data & 0x07 ) );
}
