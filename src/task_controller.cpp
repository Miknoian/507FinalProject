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

I'm thinking this should be a task and FL, FR, BL, and BR_mag should be shared variables that go to the motor driver
*/
#include <Arduino.h>
#include <PrintStream.h>
#include "task_controller.h"
#include "shares.h"

void set_direction (uint8_t dir)
    {

    }

void task_controller (void* p_params)
{
    float FL_motor = 0;
    float FR_motor = 0;
    float BL_motor = 0;
    float BR_motor = 0;
    
    FL_mag.put(0);
    FR_mag.put(0);
    BL_mag.put(0);
    BR_mag.put(0);

    FL_dir.put(0);
    FR_dir.put(0);
    BL_dir.put(0);
    BR_dir.put(0);
    
    uint8_t dir = 0;
    uint8_t mag = 1;

    //const uint8_t max_PWM = 255;
    //const uint8_t max_SPD = 10;

    for (;;)
    {
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

        FL_mag.put(FL_motor*mag);
        FR_mag.put(FR_motor*mag);
        BL_mag.put(BL_motor*mag);
        BR_mag.put(BR_motor*mag);
    }

}