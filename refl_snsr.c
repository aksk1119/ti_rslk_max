/******************************************************************************************
*
*   MODULE:
*       refl_snsr.c
*
*   DESCRIPTION:
*       This includes procedures for reflectance sensors.
*
*   Created by Seongkwan Lee on Oct 27, 2020
*
******************************************************************************************/


/*-----------------------------------------------------------------------------------------
                                     GENERAL INCLUDES
-----------------------------------------------------------------------------------------*/

#include "refl_snsr.h"

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
*       refl_snsr_init
*
*   DESCRIPTION:
*       This initializes the reflectance sensor settings.
*
********************************************************************/
void refl_snsr_init
    (
    void
    )
{
/*----------------------------------------------------------
Set the pins to GPIO mode.
----------------------------------------------------------*/
P7->SEL0 = 0x00;
P7->SEL1 = 0x00;
gpio( REFL_SNSR_LED_EVEN_PORT, REFL_SNSR_LED_EVEN_BIT );
gpio( REFL_SNSR_LED_ODD_PORT,  REFL_SNSR_LED_ODD_BIT  );

/*----------------------------------------------------------
Set the pins to OUTPUT mode
----------------------------------------------------------*/
P7->DIR = 0x00;
sbo( REFL_SNSR_LED_EVEN_PORT, REFL_SNSR_LED_EVEN_BIT );
sbo( REFL_SNSR_LED_ODD_PORT,  REFL_SNSR_LED_ODD_BIT  );

}   /* refl_snsr_init() */


/********************************************************************
*
*   PROCEDURE NAME:
*       refl_snsr_read
*
*   DESCRIPTION:
*       This will read reflectance sensor and return the value read.
*
********************************************************************/
uint8_t refl_snsr_read
    (
    uint32_t time       /* time to read light */
    )
{
/*----------------------------------------------------------
Local Constants
----------------------------------------------------------*/
#define REFL_SNSR_OUTPUT_DELAY_US 10

/*----------------------------------------------------------
Local variables
----------------------------------------------------------*/
uint8_t result;         /* sensor value to    */
                        /* return             */

/*----------------------------------------------------------
Turn on illuminate bits and make Reflectance LED
to OUTPUT and set them to high for 10us.
----------------------------------------------------------*/
out_bit_on( REFL_SNSR_LED_EVEN_PORT, REFL_SNSR_LED_EVEN_BIT );
out_bit_on( REFL_SNSR_LED_ODD_PORT,  REFL_SNSR_LED_ODD_BIT  );
P7->DIR = 0x00;
P7->OUT = 0xFF;
timer_delay_us( REFL_SNSR_OUTPUT_DELAY_US * 3 );

/*----------------------------------------------------------
Make Reflectance LED to INPUT and read the input
value.
----------------------------------------------------------*/
P7->DIR = 0xFF;
timer_delay_us( time );
result = P7->IN;

/*----------------------------------------------------------
Turn off illuminate bits to save power.
----------------------------------------------------------*/
out_bit_off( REFL_SNSR_LED_EVEN_PORT, REFL_SNSR_LED_EVEN_BIT );
out_bit_off( REFL_SNSR_LED_ODD_PORT,  REFL_SNSR_LED_ODD_BIT  );

timer_delay_ms( 30 );

return( result );

#undef REFL_SNSR_OUTPUT_DELAY_US

}   /* refl_snsr_read() */
