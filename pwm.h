#ifndef PWM_H_
#define PWM_H_

#include "util.h"

/**
 * @details  Initialize PWM outputs on P2.4, P2.5
 * @remark   Counter counts up to TA0CCR0 and back down
 * @remark   Let Timerclock period T = 8/12MHz = 666.7ns
 * @remark   P2.4=1 when timer equals TA0CCR1 on way down, P2.4=0 when timer equals TA0CCR1 on way up
 * @remark   P2.5=1 when timer equals TA0CCR2 on way down, P2.5=0 when timer equals TA0CCR2 on way up
 * @remark   Period of P2.4 is period*1.333us, duty cycle is duty1/period
 * @remark   Period of P2.5 is period*1.333us, duty cycle is duty2/period
 * @remark   Assumes 48 MHz bus clock
 * @remark   Assumes SMCLK = 48MHz/4 = 12 MHz, 83.33ns
 * @param  period is period of wave in 1.333us units
 * @param  duty1 is initial width of high pulse on P2.4 in 1.333us units
 * @param  duty2 is initial width of high pulse om P2.5 in 1.333us units
 * @return none
 * @brief  PWM on P2.4, P2.5
 */
void pwm_1_2_init
    (
    uint16_t period,
    uint16_t duty1,
    uint16_t duty2
    );


//***************************PWM_Duty1*******************************
// change duty cycle of PWM output on P2.4
// Inputs:  duty1
// Outputs: none
// period of P2.4 is 2*period*666.7ns, duty cycle is duty1/period

/**
 * @details  Set duty cycle on P2.4
 * @remark   Period of P2.4 is period*1.333us, duty cycle is duty1/period
 * @param    duty1 is width of high pulse on P2.4 in 1.333us units
 * @return   none
 * @warning  duty1 must be less than period
 * @brief    set duty cycle on PWM1
 */
void pwm_1_duty
    (
    uint16_t duty1
    );


/**
 * @details  Set duty cycle on P2.5
 * @remark   Period of P2.5 is period*1.333us, duty cycle is duty2/period
 * @param    duty2 is width of high pulse on P2.5 in 1.333us units
 * @return   none
 * @warning  duty2 must be less than period
 * @brief    set duty cycle on PWM2
 */
void pwm_2_duty
    (
    uint16_t duty2
    );


/**
 * @details  Initialize PWM outputs on P2.6, P2.7
 * @remark   Counter counts up to TA0CCR0 and back down
 * @remark   Let Timerclock period T = 8/12MHz = 666.7ns
 * @remark   P2.6=1 when timer equals TA0CCR3 on way down, P2.6=0 when timer equals TA0CCR3 on way up
 * @remark   P2.7=1 when timer equals TA0CCR4 on way down, P2.7=0 when timer equals TA0CCR4 on way up
 * @remark   Period of P2.6 is period*1.333us, duty cycle is duty3/period
 * @remark   Period of P2.7 is period*1.333us, duty cycle is duty4/period
 * @remark   Assumes 48 MHz bus clock
 * @remark   Assumes SMCLK = 48MHz/4 = 12 MHz, 83.33ns
 * @param  period is period of wave in 1.333us units
 * @param  duty3 is initial width of high pulse on P2.6 in 1.333us units
 * @param  duty4 is initial width of high pulse om P2.7 in 1.333us units
 * @return none
 * @brief  PWM on P2.6, P2.7
 */
void pwm_3_4_init
    (
    uint16_t period,
    uint16_t duty3,
    uint16_t duty4
    );


/**
 * @details  Set duty cycle on P2.6
 * @remark   Period of P2.6 is period*1.333us, duty cycle is duty3/period
 * @param    duty3 is width of high pulse on P2.6 in 1.333us units
 * @return   none
 * @warning  duty3 must be less than period
 * @brief    set duty cycle on PWM3
 */
void pwm_3_duty
    (
    uint16_t duty3
    );


/**
 * @details  Set duty cycle on P2.7
 * @remark   Period of P2.7 is period*1.333us, duty cycle is duty3/period
 * @param    duty4 is width of high pulse on P2.7 in 1.333us units
 * @return   none
 * @warning  duty4 must be less than period
 * @brief    set duty cycle on PWM4
 */
void pwm_4_duty
    (
    uint16_t duty4
    );


/**
 * @details  PWM outputs on P2.4/PM_TA0.1 (PMAP from TA1.1), P3.5/PM_UCB2CLK (PMAP from TA1.2), and P5.7/TA2.2/VREF-/VeREF-/C1.6
 * @param    period (333.33ns)
 * @param    duty0 (0<=duty0<period-1)
 * @param    duty1 (0<=duty1<period-1)
 * @param    duty2 (0<=duty2<period-1)
 * @return   none
 * SMCLK = 48MHz/4 = 12 MHz, 83.33ns<br>
 * Use clock divider of 2 to get timer clock period 166.67ns<br>
 * Counter counts up to TAnCCR0 and back down<br>
 * Let Timerclock period T = 2/12MHz = 166.67nsns<br>
 * P2.4=1 when timer equals TA1CCR1 on way down, P2.4=0 when timer equals TA1CCR1 on way up<br>
 * P3.5=1 when timer equals TA1CCR2 on way down, P3.5=0 when timer equals TA1CCR2 on way up<br>
 * P5.7=1 when timer equals TA2CCR2 on way down, P5.7=0 when timer equals TA2CCR2 on way up<br>
 * Period of P2.4 is period*333.33ns, duty cycle is duty0/period<br>
 * Period of P3.5 is period*333.33ns, duty cycle is duty1/period<br>
 * Period of P5.7 is period*333.33ns, duty cycle is duty2/period<br>
 * @brief    PWM on P2.4 P3.5 P5.7
 */
void pwm_robot_arm_init
    (
    uint16_t period,
    uint16_t duty0,
    uint16_t duty1,
    uint16_t duty2
    );


/**
 * @details  Set duty cycle on P2.4
 * @remark   Period of P2.4 is period*333.33ns, duty cycle is duty0/period
 * @param    duty0 is width of high pulse on P2.4 in 0.333us units
 * @return   none
 * @warning  duty0 must be less than period
 * @brief    set duty cycle on P2.4
 */
void pwm_robot_arm_0_duty
    (
    uint16_t duty0
    );


/**
 * @details  Set duty cycle on P3.5
 * @remark   Period of P3.5 is period*333.33ns, duty cycle is duty1/period
 * @param    duty1 is width of high pulse on P3.5 in 0.333us units
 * @return   none
 * @warning  duty1 must be less than period
 * @brief    set duty cycle on P3.5
 */
void pwm_robot_arm_1_duty
    (
    uint16_t duty1
    );


/**
 * @details  Set duty cycle on P5.7
 * @remark   Period of P5.7 is period*333.33ns, duty cycle is duty2/period
 * @param    duty2 is width of high pulse on P5.7 in 0.333us units
 * @return   none
 * @warning  duty2 must be less than period
 * @brief    set duty cycle on P5.7
 */
void pwm_robot_arm_2_duty
    (
    uint16_t duty2
    );


/**
 * @details  get duty cycle on P2.4
 * @remark   Period of P2.4 is period*333.33ns, duty cycle is duty0/period
 * @param    none
 * @return   duty0 is width of high pulse on P2.4 in 0.333us units
 * @brief    get duty cycle on P2.4
 */
uint16_t pwm_robot_arm_get_0_duty
    (
    void
    );


/**
 * @details  get duty cycle on P3.5
 * @remark   Period of P3.5 is period*333.33ns, duty cycle is duty1/period
 * @param    none
 * @return   duty1 is width of high pulse on P3.5 in 0.333us units
 * @brief    get duty cycle on P3.5
 */
uint16_t pwm_robot_arm_get_1_duty
    (
    void
    );


/**
 * @details  get duty cycle on P5.7
 * @remark   Period of P5.7 is period*333.33ns, duty cycle is duty2/period
 * @param    none
 * @return   duty2 is width of high pulse on P5.7 in 0.333us units
 * @brief    get duty cycle on P5.7
 */
uint16_t pwm_robot_arm_get_2_duty
    (
    void
    );


#endif /* PWM_H_ */
