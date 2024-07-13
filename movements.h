/*
 * movements.h
 *
 *  Created on: Nov 5, 2020
 *      Author: aksk1
 */

#ifndef MOVEMENTS_H_
#define MOVEMENTS_H_

#include <refl_snsr.h>
#include <stdint.h>
#include <stdio.h>

#include "msp.h"
#include "timer.h"
#include "motor.h"

typedef uint8_t line_sensor_type_t;
enum {
    LINE_FOLLOWING,
    LINE_LEFT,
    LINE_RIGHT,
    LINE_ALL
};



uint8_t IR_Tracing
    (
    uint16_t speed
    );


void Motor_Turn_ARM
    (
    uint8_t dir
    );


void Motor_Turn_ARM1
    (
    uint8_t dir
    );


void Arduino_Init
    (
    void
    );


void Arduino_OUT_ON
    (
    void
    );


void Arduino_OUT_OFF
    (
    void
    );


uint8_t Arduino_Input
    (
    void
    );


#endif /* MOVEMENTS_H_ */
