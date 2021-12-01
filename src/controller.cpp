/** @file   controller.cpp
 * 
 *  @author Joshua Hoye
 *  @date   11/30/2021
 */
 
/*
    This task takes inputs from the wifi task to set desired direction and speed, sends the apropriate pwm to the motors, 
    and takes encoder readings to adjust PWM to achive desired speed. 
*/

//NOTE: Incomplete. Will take in the shared 

#include <Arduino.h>
#include "controller.h"

void direction (uint16_t dir)
{
    int FL_motor = 0;
    int FR_motor = 0;
    int BL_motor = 0;
    int BR_motor = 0;

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
}