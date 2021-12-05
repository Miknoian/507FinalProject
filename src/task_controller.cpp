/** @file   controller.cpp
 * 
 *  @author Joshua Hoye
 *  @date   11/30/2021
 */
 
/*
    This task takes inputs from the wifi task to set desired direction and speed, sends the apropriate pwm to the motors, 
    and takes encoder readings to adjust PWM to achive desired speed. 
*/

/*NOTE: Incomplete. Not sure if this shoukd be a task of its own or simply a function called by the motor driver. 

Controller function takes a direction input and creates a scaler for the desired speed on each motor. This will 
then be multiplied by the desired overall nominal speed to get the nominal speed for each motor.

I'm thinking this should be a task and FL, FR, BL, and BR_pwm should be shared variables that go to the motor driver
*/
#include <Arduino.h>
#include <PrintStream.h>
#include "task_controller.h"
#include "shares.h"

void task_controller (void* p_params)
{   
    float FL_relative = 0;
    float FR_relative = 0;
    float BL_relative = 0;
    float BR_relative = 0;
    uint8_t FL_pwm = 0;
    uint8_t FR_pwm = 0;
    uint8_t BL_pwm = 0;
    uint8_t BR_pwm = 0;
    const uint8_t max_pwm = 255;
    const uint8_t max_SPD = 10;
    uint32_t dir = 0;
    uint16_t mag = 0;
    for(;;)
    {
        mag = stickMag.get();
        dir = stickAngle.get();
        //Serial.println("Angle share is: ");
        //Serial.println(dir);
        //If panning E / NE


        if (dir >= 0 && dir < 90)   //These if statements produce the relative speed of each motor
        {
            FL_relative = -1 + 2*(dir/90);
            FR_relative = 1;
            BL_relative = 1;
            BR_relative = -1 + 2*(dir/90);
        }

        //If panning N/NW
        if (dir-90 >= 0 && dir-90 < 90)
        {
            FL_relative = 1;
            FR_relative = 1-2*((dir-90)/90);
            BL_relative = 1-2*((dir-90)/90);
            BR_relative = 1;
        }

        //If panning W/SW
        if (dir-180 >= 0 && dir-180 < 90)
        {
            FL_relative = 1-2*((dir-180)/90);
            FR_relative = -1;
            BL_relative = -1;
            BR_relative = 1-2*((dir-180)/90);
        }

        //If panning S/SE
        if (dir-270 >= 0 && dir-270 < 90)
        {
            FL_relative = -1;
            FR_relative = -1 + 2*((dir-270)/90);
            BL_relative = -1 + 2*((dir-270)/90);
            BR_relative = -1;
        }
        vTaskDelay(5);
        
        //Ideal speed = max_speed*FL_relative*
        //mag = mag/100;

        /*
        FL_pwm = dir*mag*max_pwm;
        FR_pwm = dir*mag*max_pwm;
        BL_pwm = dir*mag*max_pwm;
        BR_pwm = dir*mag*max_pwm;
        */

    }
}