/** @file   task_motor.cpp
 * 
 *  @author Joshua Hoye
 *  @date   11/30/2021
 */
#include <Arduino.h>
#include <PrintStream.h>
#include "task_motor.h"
#include "class_motor.h"
#include "shares.h"

/*
NOTE: PINS MUST BE DECLARED IN MAIN FILE!
For these motors, copy paste the following into the setup of the main file:

    const uint16_t PWM_Freq = 1000;
    const uint8_t PWM_Res = 8;

    ledcAttachPin(33, 0);
    ledcAttachPin(25, 1);
    ledcAttachPin(26, 2);
    ledcAttachPin(27, 3);
    ledcAttachPin(18, 4);
    ledcAttachPin(19, 5);
    ledcAttachPin(17, 6);
    ledcAttachPin(5, 7);

    ledcSetup(0, PWM_Freq, PWM_Res);
    ledcSetup(1, PWM_Freq, PWM_Res);
    ledcSetup(2, PWM_Freq, PWM_Res);
    ledcSetup(3, PWM_Freq, PWM_Res);
    ledcSetup(4, PWM_Freq, PWM_Res);
    ledcSetup(5, PWM_Freq, PWM_Res);
    ledcSetup(6, PWM_Freq, PWM_Res);
    ledcSetup(7, PWM_Freq, PWM_Res);
*/

//Pins we cant use for PWM:    34, 35, 36, 37, 38, 39

uint32_t mag = 0;

void task_motor_0 (void* p_params)
{
    uint8_t MOTOR_IN1 = 33;
    uint8_t MOTOR_IN2 = 25;
    uint8_t PWM_Ch1 = 0;
    uint8_t PWM_Ch2 = 1;

    //Create motor object
    Motor Motor_0 (MOTOR_IN1, MOTOR_IN2, PWM_Ch1, PWM_Ch2);
    //FL
    for (;;)
    {
        mag = FL_pwm.get();
        Motor_0.run(mag, 1);
        vTaskDelay(5);
    }
}

void task_motor_1 (void* p_params)
{
    uint8_t MOTOR_IN1 = 14;
    uint8_t MOTOR_IN2 = 27;
    uint8_t PWM_Ch1 = 2;
    uint8_t PWM_Ch2 = 3;

    Motor Motor_1 (MOTOR_IN1, MOTOR_IN2, PWM_Ch1, PWM_Ch2);
    //BL
    for (;;)
    {
        mag = BL_pwm.get();
        Motor_1.run(mag, 1);
        vTaskDelay(5);
    }
}

void task_motor_2 (void* p_params)
{
    uint8_t MOTOR_IN2 = 18;
    uint8_t MOTOR_IN1 = 19;
    uint8_t PWM_Ch1 = 4;
    uint8_t PWM_Ch2 = 5;

    Motor Motor_2 (MOTOR_IN1, MOTOR_IN2, PWM_Ch1, PWM_Ch2);
    //FR
    for (;;)
    {
        mag = FR_pwm.get();
        Motor_2.run(mag, 1);
        vTaskDelay(5);
    }
}

void task_motor_3 (void* p_params)
{
    uint8_t MOTOR_IN2 = 17;
    uint8_t MOTOR_IN1 = 5;
    uint8_t PWM_Ch1 = 6;
    uint8_t PWM_Ch2 = 7;

    Motor Motor_3 (MOTOR_IN1, MOTOR_IN2, PWM_Ch1, PWM_Ch2);
    //BR
    for (;;)
    {
        mag = BR_pwm.get();
        Motor_3.run(mag, 1);
        vTaskDelay(5); 
    }
}
