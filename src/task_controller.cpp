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
    //A scaler that represents the speed relative to the other motors.
    float FL_relativeSpeed = 0;
    float BL_relativeSpeed = 0;
    float FR_relativeSpeed = 0;
    float BR_relativeSpeed = 0;

    //Represents the ideal rps of the motor
    // int32_t FL_idealSpeed = 0;
    // int32_t FR_idealSpeed = 0;
    // int32_t BL_idealSpeed = 0;
    // int32_t BR_idealSpeed = 0;

    int32_t idealSpeed[] = {0,0,0,0};
    int32_t realSpeed[] = {0,0,0,0};
    int32_t integral_error[] = {0,0,0,0};
    int32_t pwm[] = {0,0,0,0};

    float P_gain = 1;
    float I_gain = 1;


    //The specified output to the motor to achive ideal speed
    uint8_t FL_pwm = 0;
    uint8_t FR_pwm = 0;
    uint8_t BL_pwm = 0;
    uint8_t BR_pwm = 0;

    const uint8_t max_pwm = 255;
    const int32_t max_Speed = 10;
    
    uint32_t dir = 0;
    float mag = 0;

    for(;;)
    {
        mag = stickMag.get()/100;   //make mag a scaler from 0-1.
        dir = stickAngle.get();
        //Serial.println("Angle share is: ");
        //Serial.println(dir);
       
        //If panning E / NE
        if (dir >= 0 && dir < 90)   //These if statements produce the relative speed of each motor
        {
            FL_relativeSpeed = -1 + 2*(dir/90);
            FR_relativeSpeed = 1;
            BL_relativeSpeed = 1;
            BR_relativeSpeed = -1 + 2*(dir/90);
        }

        //If panning N/NW
        if (dir-90 >= 0 && dir-90 < 90)
        {
            FL_relativeSpeed = 1;
            FR_relativeSpeed = 1-2*((dir-90)/90);
            BL_relativeSpeed = 1-2*((dir-90)/90);
            BR_relativeSpeed = 1;
        }

        //If panning W/SW
        if (dir-180 >= 0 && dir-180 < 90)
        {
            FL_relativeSpeed = 1-2*((dir-180)/90);
            FR_relativeSpeed = -1;
            BL_relativeSpeed = -1;
            BR_relativeSpeed = 1-2*((dir-180)/90);
        }

        //If panning S/SE
        if (dir-270 >= 0 && dir-270 < 90)
        {
            FL_relativeSpeed = -1;
            FR_relativeSpeed = -1 + 2*((dir-270)/90);
            BL_relativeSpeed = -1 + 2*((dir-270)/90);
            BR_relativeSpeed = -1;
        }
        vTaskDelay(5);
        
        idealSpeed[0] = mag*FL_relativeSpeed*max_Speed;
        idealSpeed[1] = mag*BL_relativeSpeed*max_Speed;
        idealSpeed[2] = mag*FR_relativeSpeed*max_Speed;
        idealSpeed[3] = mag*BR_relativeSpeed*max_Speed;

        realSpeed[0] = enc0_RPS.get();
        realSpeed[1] = enc1_RPS.get();
        realSpeed[2] = enc2_RPS.get();
        realSpeed[3] = enc3_RPS.get();

        for (uint8_t n=0; n >= 3; n++)
        {
            pwm[n] = (idealSpeed[n]-realSpeed[n])*P_gain;
            integral_error[n] += idealSpeed[n]-realSpeed[n];
            
            pwm[n] += integral_error[n]*I_gain;

            if (pwm[n] > 255)
            {
                pwm[n] = 255;
            }

        }


        /*
        FL_pwm = dir*mag*max_pwm;
        FR_pwm = dir*mag*max_pwm;
        BL_pwm = dir*mag*max_pwm;
        BR_pwm = dir*mag*max_pwm;
        */

    }
}