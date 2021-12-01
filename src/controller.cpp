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

I'm thinking this should be a task and FL, FR, BL, and BR_PWM should be shared variables that go to the motor driver
*/
#include <Arduino.h>
#include "controller.h"

void compute (uint16_t dir, uint16_t mag)
{
    const uint8_t max_PWM = 255;

    float FL_motor = 0;
    float FR_motor = 0;
    float BL_motor = 0;
    float BR_motor = 0;

    uint8_t FL_PWM = 0;
    uint8_t FR_PWM = 0;
    uint8_t BL_PWM = 0;
    uint8_t BR_PWM = 0;

    //If panning E / NE
    if (dir >= 0 && dir < 90)
    {
        FL_motor = -1 + 2*(dir/90);
        FR_motor = 1;
        BL_motor = 1;
        BR_motor = -1 + 2*(dir/90);
    }

    //If panning N/NW
    if (dir-90 >= 0 && dir-90 < 90)
    {
        FL_motor = 1;
        FR_motor = 1-2*((dir-90)/90);
        BL_motor = 1-2*((dir-90)/90);
        BR_motor = 1;
    }

    //If panning W/SW
    if (dir-180 >= 0 && dir-180 < 90)
    {
        FL_motor = 1-2*((dir-180)/90);
        FR_motor = -1;
        BL_motor = -1;
        BR_motor = 1-2*((dir-180)/90);
    }

    //If panning S/SE
    if (dir-270 >= 0 && dir-270 < 90)
    {
        FL_motor = -1;
        FR_motor = -1 + 2*((dir-270)/90);
        BL_motor = -1 + 2*((dir-270)/90);
        BR_motor = -1;
    }

    mag = mag/100;

    FL_PWM = dir*mag*max_PWM;
    FL_PWM = dir*mag*max_PWM;
    FL_PWM = dir*mag*max_PWM;
    FL_PWM = dir*mag*max_PWM;


}