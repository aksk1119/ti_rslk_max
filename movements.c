/******************************************************************************************
*
*   MODULE:
*       movements.c
*
*   DESCRIPTION:
*       This file includes robot movement related procedures.
*
*   Created by Seongkwan Lee on Oct 27, 2020
*
******************************************************************************************/


/*-----------------------------------------------------------------------------------------
                                     GENERAL INCLUDES
-----------------------------------------------------------------------------------------*/

#include "movements.h"

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

/*-----------------------------------------------------------------------------------------
                                        VARIABLES
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
                                       PROCEDURES
-----------------------------------------------------------------------------------------*/


/********************************************************************
*
*   PROCEDURE NAME:
*       IR_Tracing
*
*   DESCRIPTION:
*       Trace black line with IR sensor
*
********************************************************************/

uint8_t IR_Tracing
    (
    uint16_t speed
    )
{
#define KP 4
#define KI 0.0002
#define KD 1.5

float turn_speed;
int16_t PID_VAL;
uint8_t sensor_read;
uint8_t sensor_left;
uint8_t sensor_right;
boolean sensor_0;
boolean sensor_1;
boolean sensor_2;
boolean sensor_3;
boolean sensor_4;
boolean sensor_5;
boolean sensor_6;
boolean sensor_7;

static float err_I = 0;
static float err_D = 0;
static float err_B = 0;
static float err_P = 0;
static uint8_t count = 0;

sensor_read = refl_snsr_read(1000);

sensor_0 = ((sensor_read & 0x01) == 0x01);
sensor_1 = ((sensor_read & 0x02) == 0x02);
sensor_2 = ((sensor_read & 0x04) == 0x04);
sensor_3 = ((sensor_read & 0x08) == 0x08);
sensor_4 = ((sensor_read & 0x10) == 0x10);
sensor_5 = ((sensor_read & 0x20) == 0x20);
sensor_6 = ((sensor_read & 0x40) == 0x40);
sensor_7 = ((sensor_read & 0x80) == 0x80);

sensor_left = sensor_4 + sensor_5 + sensor_6 + sensor_7;
sensor_right = sensor_0 + sensor_1 + sensor_2 + sensor_3;

if( sensor_read == 0x00 )
    {
    count++;
    if ( count > 100 )
        {
        count = 0;
        return 4;
        }
    }
else
    {
    count = 0;
    }

if( ( sensor_left  > 2 )
 && ( sensor_right > 2 ) )
    {
    return( LINE_ALL );
    }

if( ( sensor_left  > 2 )
 && ( sensor_right < 2 ) )
    {
    return( LINE_LEFT );
    }

if( ( sensor_left  < 2 )
 && ( sensor_right > 2 ) )
    {
    return( LINE_RIGHT );
    }

if( sensor_read )
    {
    turn_speed = ( float )( sensor_0 * ( 2.0 ) + sensor_1 * ( 0.7 )
            + sensor_2 * ( 0.4 ) + sensor_3 * ( 0.1 ) + sensor_7 * ( -2.0 )
            + sensor_6 * ( -0.7 ) + sensor_5 * ( -0.4 ) + sensor_4 * ( -0.1 ) );
    err_P = turn_speed * 600;
    }
else
    {
    err_P = err_B;
    }

err_I += err_P;
err_D = err_B - err_P;
err_B = err_P;

PID_VAL = ( int16_t )( ( err_P * KP ) + ( err_I * KI ) + ( err_D * KD ) );

motor_move_with_forward_and_turn( speed, PID_VAL );

return( LINE_FOLLOWING );

#undef KP
#undef KI
#undef KD

}   /* IR_Tracing() */


/********************************************************************
*
*   PROCEDURE NAME:
*       Motor_Turn_ARM
*
*   DESCRIPTION:
*       Make smooth turn
*
********************************************************************/

void Motor_Turn_ARM
    (
    uint8_t dir
    )
{
if( dir == 3 )
    {
    // Motor_Left( 2500, 6000 );
    timer_delay_ms(400);
    motor_stop();
    }
else if( dir == 4 )
    {
    // Motor_Right( 6000, 2500 );
    timer_delay_ms(400);
    motor_stop();
    }

}   /* Motor_Turn_ARM() */


/********************************************************************
*
*   PROCEDURE NAME:
*       Motor_Turn_ARM1
*
*   DESCRIPTION:
*       Make smooth turn
*
********************************************************************/

void Motor_Turn_ARM1
    (
    uint8_t dir
    )
{
if( dir == 3 )
    {
    // Motor_Left( 3500, 6000 );
    timer_delay_ms(400);
    motor_stop();
    }
else if( dir == 4 )
    {
    // Motor_Right( 6000, 3500 );
    timer_delay_ms(400);
    motor_stop();
    }
}


/********************************************************************
*
*   PROCEDURE NAME:
*       Arduino_Init
*
*   DESCRIPTION:
*       Initialize Arduino connection pins
*
********************************************************************/

void Arduino_Init
    (
    void
    )
{
P4->SEL0 &= ~0x10;
P4->SEL1 &= ~0x10;
P4->DIR |= 0x10;
P4->OUT &= ~0x10;

P6->SEL0 &= ~0x02;
P6->SEL1 &= ~0x02;
P6->DIR &= ~0x02;
}


/********************************************************************
*
*   PROCEDURE NAME:
*       Arduino_OUT_OFF
*
*   DESCRIPTION:
*       Turn off Arduino OUT pin
*
********************************************************************/

void Arduino_OUT_OFF
    (
    void
    )
{
P4->OUT &= ~0x10;

}   /* Arduino_OUT_OFF() */

void Arduino_OUT_ON
    (
    void
    )
{
P4->OUT |= 0x10;
}

uint8_t Arduino_Input
    (
    void
    )
{
return( P6->IN & 0x02 );
}
