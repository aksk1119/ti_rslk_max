/******************************************************************************************
*
*   MODULE:
*       tachometer.c
*
*   DESCRIPTION:
*       This file includes tachometer related procedures.
*
*   Created by Seongkwan Lee on Oct 27, 2020
*
******************************************************************************************/

/*-----------------------------------------------------------------------------------------
                                    GENERAL INCLUDES
-----------------------------------------------------------------------------------------*/

#include <stdint.h>

#include "msp.h"
#include "tachometer.h"
#include "timer.h"
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

/*-----------------------------------------------------------------------------------------
                                        VARIABLES
-----------------------------------------------------------------------------------------*/

uint16_t                tachometer_first_right_time;
uint16_t                tachometer_second_right_time;
uint16_t                tachometer_first_left_time;
uint16_t                tachometer_second_left_time;
int32_t                 tachometer_right_steps;
int32_t                 tachometer_left_steps;
tach_dir_t8             tachometer_right_dir;
tach_dir_t8             tachometer_left_dir;

/*-----------------------------------------------------------------------------------------
                                       PROCEDURES
-----------------------------------------------------------------------------------------*/

static void tachometer_right_int
    (
    uint16_t currenttime
    );

static void tachometer_left_int
    (
    uint16_t currenttime
    );


/********************************************************************
*
*   PROCEDURE NAME:
*       tachometer_right_int
*
*   DESCRIPTION:
*       Interrupt function for right side tachometer.
*
********************************************************************/

static void tachometer_right_int
    (
    uint16_t currenttime
    )
{
tachometer_first_right_time  = tachometer_second_right_time;
tachometer_second_right_time = currenttime;

/*---------------------------------------------------------
Encoder B is low, so this is a step backward
---------------------------------------------------------*/
if( ( P5->IN & 0x01 ) == 0 )
    {
    tachometer_right_steps = tachometer_right_steps - 1;
    tachometer_right_dir   = TACH_DIR_REVERSE;
    }

/*---------------------------------------------------------
Encoder B is high, so this is a step backward
---------------------------------------------------------*/
else
    {
    tachometer_right_steps = tachometer_right_steps + 1;
    tachometer_right_dir   = TACH_DIR_FORWARD;
    }

}   /* tachometer_right_int() */


/********************************************************************
*
*   PROCEDURE NAME:
*       tachometer_left_int
*
*   DESCRIPTION:
*       Interrupt function for left side tachometer.
*
********************************************************************/

static void tachometer_left_int
    (
    uint16_t currenttime
    )
{
tachometer_first_left_time  = tachometer_second_left_time;
tachometer_second_left_time = currenttime;

/*---------------------------------------------------------
Encoder B is low, so this is a step backward
---------------------------------------------------------*/
if( ( P5->IN & 0x04 ) == 0 )
    {
    tachometer_left_steps = tachometer_left_steps - 1;
    tachometer_left_dir   = TACH_DIR_REVERSE;
    }

/*---------------------------------------------------------
Encoder B is high, so this is a step backward
---------------------------------------------------------*/
else
    {
    tachometer_left_steps = tachometer_left_steps + 1;
    tachometer_left_dir   = TACH_DIR_FORWARD;
    }

}   /* tachometer_left_int() */


/********************************************************************
*
*   PROCEDURE NAME:
*       tachometer_init
*
*   DESCRIPTION:
*       Initialize GPIO pins for input, which will be used to
*       determine the direction of rotation. Initialize the input
*       capture interface, which will be used to measure the speed of
*       rotation.
*
********************************************************************/

void tachometer_init
    (
    void
    )
{
/*---------------------------------------------------------
P10.5 ELA
---------------------------------------------------------*/
gpio( P10, 5 );
sbi( P10, 5 );

/*---------------------------------------------------------
P10.4 ERA
---------------------------------------------------------*/
gpio( P10, 4 );
sbi( P10, 4 );

/*---------------------------------------------------------
P5.2 ELB
---------------------------------------------------------*/
gpio( P5, 2 );
sbi( P5, 2 );

/*---------------------------------------------------------
P5.0 ERA
---------------------------------------------------------*/
gpio( P5, 0 );
sbi( P5, 0 );

/*---------------------------------------------------------
Initialize interface for timer A3 capture IRQ to tachometer
logics.
---------------------------------------------------------*/
timer_a3_capture_register_callback( &tachometer_right_int, &tachometer_left_int );

/*---------------------------------------------------------
Initialize variables.
---------------------------------------------------------*/
tachometer_right_steps = 0;
tachometer_left_steps  = 0;
tachometer_right_dir   = TACH_DIR_STOPPED;
tachometer_left_dir    = TACH_DIR_STOPPED;

}   /* tachometer_init() */


/********************************************************************
*
*   PROCEDURE NAME:
*       tachometer_get
*
*   DESCRIPTION:
*       Get the most recent tachometer measurements.
*
*   NOTE:
*       Assumes tachometer_init() and timer_init_48_mhz() has been
*       called prior to calling this function.
*
********************************************************************/

void tachometer_get
    (
    uint16_t *          left_tach,
    tach_dir_t8 *       left_dir,
    int32_t *           left_steps,
    uint16_t *          right_tach,
    tach_dir_t8 *       right_dir,
    int32_t *           right_steps
    )
{
/*---------------------------------------------------------
Get left tachometer info.
---------------------------------------------------------*/
*left_tach    = (tachometer_second_left_time - tachometer_first_left_time);
*left_dir     = tachometer_left_dir;
*left_steps   = tachometer_left_steps;

/*---------------------------------------------------------
Get right tachometer info.
---------------------------------------------------------*/
*right_tach   = (tachometer_second_right_time - tachometer_first_right_time);
*right_dir    = tachometer_right_dir;
*right_steps  = tachometer_right_steps;

}   /* tachometer_get() */


/********************************************************************
*
*   PROCEDURE NAME:
*       tachometer_reset
*
*   DESCRIPTION:
*       Reset the tachometer measurements
*
********************************************************************/

void tachometer_reset
    (
    void
    )
{
tachometer_right_steps = 0;
tachometer_left_steps  = 0;
tachometer_right_dir   = TACH_DIR_STOPPED;
tachometer_left_dir    = TACH_DIR_STOPPED;

}   /* tachometer_reset() */
