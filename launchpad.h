#ifndef LAUNCHPAD_H_
#define LAUNCHPAD_H_

#include "util.h"

/**
 * \brief red color P2.2-P2.0 LED
 */
#define RED       0x01
/**
 * \brief green color P2.2-P2.0 LED
 */
#define GREEN     0x02
/**
 * \brief blue color P2.2-P2.0 LED
 */
#define BLUE      0x04

/**
 * Initialize LaunchPad I/O
 *
 * @param  none
 * @return none
 * @brief  Initialize Switch inputs and LED outputs
 */
void launchpad_init
    (
    void
    );


/**
 * Input from two switches on LaunchPad
 * Value returned in postive logic
 *
 * @param  none
 * @return two-bit value of switches
 *         0x00 none
 *         0x01 Button1
 *         0x02 Button2
 *         0x03 both Button1 and Button2
 * @brief  Input from Switches
 */
uint8_t launchpad_buttons_read
        (
        void
        );


/**
 * Output to red LED on LaunchPad
 *
 * @param  data is value to send to LED,
 * 0 is off; 1 is on
 * @return none
 * @brief  Output to red LED
 */
void launchpad_led_ctrl
    (
    uint8_t data
    );


/**
 * Output to 3-color LED on LaunchPad
 *
 * @param  data is value to send to LEDs
 * 0 is off; bit0 is red; bit1 is green; bit2 is blue
 * @return none
 * @brief  Output to 3-color LED
 */
void launchpad_3_color_led_ctrl
    (
    uint8_t data
    );

#endif
