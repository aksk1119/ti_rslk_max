/*-----------------------------------------------------------------------------------------
                                    GENERAL INCLUDES
-----------------------------------------------------------------------------------------*/

#include <stdio.h>

#include "util.h"
#include "bump.h"
#include "timer.h"
#include "motor.h"
#include "switch.h"
#include "movements.h"
#include "launchpad.h"
#include "refl_snsr.h"
#include "tachometer.h"

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

static void Mission0
    (
    void
    );

static void Mission1
    (
    void
    );

static void Mission2
    (
    void
    );

static void Mission3
    (
    void
    );

static void Mission4
    (
    void
    );

static void Mission5
    (
    void
    );


/********************************************************************
*
*   PROCEDURE NAME:
*       Mission0
*
*   DESCRIPTION:
*       Mission 0
*
********************************************************************/

static void Mission0
    (
    void
    )
{
/**********************************************************
Local variables
**********************************************************/
uint8_t                 bump;
uint8_t                 cnt;
uint8_t                 sensor_read;
uint8_t                 sensor_0;
uint8_t                 sensor_1;
uint8_t                 sensor_2;
uint8_t                 sensor_3;
uint8_t                 sensor_4;
uint8_t                 sensor_5;
uint8_t                 sensor_6;
uint8_t                 sensor_7;

/**********************************************************
Initialize local variables
**********************************************************/
cnt = 10;

/**********************************************************
Use bumper to select IR sensor sensitivity
**********************************************************/
while( TRUE )
    {
    sensor_read = refl_snsr_read( cnt * 100 );
    sensor_0 = ( ( sensor_read & 0x01 ) == 0x01 );
    sensor_1 = ( ( sensor_read & 0x02 ) == 0x02 );
    sensor_2 = ( ( sensor_read & 0x04 ) == 0x04 );
    sensor_3 = ( ( sensor_read & 0x08 ) == 0x08 );
    sensor_4 = ( ( sensor_read & 0x10 ) == 0x10 );
    sensor_5 = ( ( sensor_read & 0x20 ) == 0x20 );
    sensor_6 = ( ( sensor_read & 0x40 ) == 0x40 );
    sensor_7 = ( ( sensor_read & 0x80 ) == 0x80 );

    printf( "%d %d %d %d %d %d %d %d: %d\n",
            sensor_7,sensor_6, sensor_5, sensor_4, sensor_3, sensor_2, sensor_1, sensor_0, cnt * 100 );

    bump = bump_read();

    if( ( bump & BUMP_0 ) == 0 )
        {
        while( ( bump_read() & BUMP_0 ) == 0 );     // wait for release
        cnt++;
        timer_delay_ms( 300 );
        }
    else if( ( bump & BUMP_1 ) == 0 )
        {
        while( ( bump_read() & BUMP_1 ) == 0 );     // wait for release
        if( cnt > 0 )
            {
            cnt--;
            }
        timer_delay_ms( 300 );
        }
    }

}   /* Mission0 */


/********************************************************************
*
*   PROCEDURE NAME:
*       Mission1
*
*   DESCRIPTION:
*       Mission 1
*
********************************************************************/

static void Mission1
    (
    void
    )
{
motor_move_with_forward_and_turn(5000, 0);
timer_delay_ms(1000);
motor_stop();
motor_move_with_forward_and_turn(0, 5000);
timer_delay_ms(1000);
motor_stop();

}   /* Mission1() */


/********************************************************************
*
*   PROCEDURE NAME:
*       Mission2
*
*   DESCRIPTION:
*       Mission 2
*
********************************************************************/

static void Mission2
    (
    void
    )
{
int32_t                 steps_left;
int32_t                 steps_right;

tachometer_reset();
motor_move_with_forward_and_turn( 3000, 0 );
while( TRUE )
    {
    tachometer_get( NULL, NULL, &steps_left, NULL, NULL, &steps_right );
    if( ( abs( steps_left  ) >= 1000 )
     || ( abs( steps_right ) >= 1000 ) )
        {
        break;
        }
    timer_delay_ms(100);
    }
motor_stop();
}   /* Mission2() */


static void Mission3
    (
    void
    )
{
uint8_t check_read;
while( TRUE )
    {
    check_read = IR_Tracing( 6000 );
    printf( "%1d\n", check_read );
    }

}

static void Mission4
    (
    void
    )
{
timer_delay_ms( 300 );
bump_wait(BUMP_0);

}

static void Mission5
    (
    void
    )
{
Motor_Turn_ARM1( 3 );

}

/************************************/
// Color    LED(s) Port2
// dark     ---    0
// red      R--    0x01
// green    -G-    0x02
// yellow   RG-    0x03
// blue     --B    0x04
// pink     R-B    0x05
// sky blue -GB    0x06
// white    RGB    0x07

int main
    (
    void
    )
{
/**********************************************************
Local variables
**********************************************************/
uint8_t                 cnt;
uint8_t                 bump;

/**********************************************************
Initialize local variables
**********************************************************/
cnt = 0;

/**********************************************************
Call initialization functions
**********************************************************/
timer_init_48_mhz();
//Arduino_Init();       // GPIO Communication with Arduino
launchpad_init();       // built-in switches and LEDs
bump_init();            // bump switches
motor_init();
refl_snsr_init();
switch_init();          // main board switches
tachometer_init();

/**********************************************************
Use bumper to select mission
**********************************************************/
while( TRUE )
    {
    timer_delay_ms( 1 );
    bump = bump_read();
    if( ( bump & BUMP_0 ) == 0 )
        {
        while( ( bump_read() & BUMP_0 ) == 0 );     // wait for release
        if(cnt < 5)
            {
            cnt++;
            }
        launchpad_3_color_led_ctrl( cnt );
        timer_delay_ms( 300 );
        }
    else if( ( bump & BUMP_1 ) == 0 )
        {
        while( ( bump_read() & BUMP_1 ) == 0 );     // wait for release
        if( cnt > 0 )
            {
            cnt--;
            }
        launchpad_3_color_led_ctrl( cnt );
        timer_delay_ms( 300 );
        }
    else if( ( bump & BUMP_2 ) == 0 )
        {
        while( ( bump_read() & BUMP_3 ) == 0 );     // wait for release
        timer_delay_ms( 300 );
        if( cnt == 0 )
            {
            Mission0();
            }
        else if( cnt == 1 )
            {
            Mission1();
            }
        else if( cnt == 2 )
            {
            Mission2();
            }
        else if( cnt == 3 )
            {
            Mission3();
            }
        else if( cnt == 4 )
            {
            Mission4();
            }
        else if( cnt == 5 )
            {
            Mission5();
            }
        }
    }

}

