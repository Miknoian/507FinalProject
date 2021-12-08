/** @file   task_motor.cpp
 *  @brief Task to run motors
 *  @details This task contains four functions for each motor. Each function creates a separate object of a motor from the motor class. The parameters for the
 *  motors are then specified, which are the pins. The function then runs the "run" function of each object in a forever loop
 *  @author Joshua Hoye
 *  @date   11/30/2021
 */
#include <Arduino.h>
#include <PrintStream.h>
#include "task_motor.h"
#include "class_motor.h"
#include "shares.h"

//NOTE: PINS MUST BE DECLARED IN MAIN FILE!
//For these motors, copy paste the following into the setup of the main file:
//Pins we cant use for PWM:    34, 35, 36, 37, 38, 39

/**
 * @brief Function to run Motor 1
 */
void task_motor_0 (void* p_params)
{
    uint8_t MOTOR_IN1 = 33; // Pin 1 for motor 1
    uint8_t MOTOR_IN2 = 25; // Pin 2 for motor 1
    uint8_t PWM_Ch1 = 0; // PWM Channel 1
    uint8_t PWM_Ch2 = 1; // PWM Channel 1

    //Create motor object
    Motor Motor_0 (MOTOR_IN1, MOTOR_IN2, PWM_Ch1, PWM_Ch2);
    //FL
    for (;;)
    {
        Motor_0.run(FL_pwm.get(), FL_dir.get());
        vTaskDelay(10);
    }
}

/**
 * @brief Function to run Motor 2
 */
void task_motor_1 (void* p_params)
{
    uint8_t MOTOR_IN1 = 14; // Pin 1 for motor 2
    uint8_t MOTOR_IN2 = 27; // Pin 2 for motor 2
    uint8_t PWM_Ch1 = 2; // PWM Channel 1
    uint8_t PWM_Ch2 = 3; // PWM Channel 2

    Motor Motor_1 (MOTOR_IN1, MOTOR_IN2, PWM_Ch1, PWM_Ch2);
    //BL
    for (;;)
    {
        Motor_1.run(BL_pwm.get(), BL_dir.get());
        vTaskDelay(10);
    }
}

/**
 * @brief Function to run Motor 3
 */
void task_motor_2 (void* p_params)
{
    uint8_t MOTOR_IN2 = 18; // Pin 1 for motor 3
    uint8_t MOTOR_IN1 = 19; // Pin 2 for motor 3
    uint8_t PWM_Ch1 = 4; // PWM Channel 1
    uint8_t PWM_Ch2 = 5; // PWM Channel 2

    Motor Motor_2 (MOTOR_IN1, MOTOR_IN2, PWM_Ch1, PWM_Ch2);
    //FR
    for (;;)
    {
        Motor_2.run(FR_pwm.get(), FR_dir.get());
        vTaskDelay(10);
    }
}

/**
 * @brief Function to run Motor 4
 */
void task_motor_3 (void* p_params)
{
    uint8_t MOTOR_IN2 = 17; // Pin 1 for motor 4
    uint8_t MOTOR_IN1 = 5; // Pin 2 for motor 4
    uint8_t PWM_Ch1 = 6; // PWM Channel 1
    uint8_t PWM_Ch2 = 7; // PWM Channel 2

    Motor Motor_3 (MOTOR_IN1, MOTOR_IN2, PWM_Ch1, PWM_Ch2);
    //BR
    for (;;)
    {
        Motor_3.run(BR_pwm.get(), BR_dir.get());
        vTaskDelay(10); 
    }
}
