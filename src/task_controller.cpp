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
    float realSpeed[] = {0,0,0,0};
    int32_t integral_error[] = {0,0,0,0};
    int32_t pwm[] = {0,0,0,0};
    int32_t deriv_error[] = {0,0,0,0};
    int32_t e_prior[] = {0,0,0,0};

    float P_gain = 3.5;
    float I_gain = 0.1;
    float D_gain= 0.001;

    const uint32_t max_pwm = 255;
    const int32_t max_Speed = 30;
    
    uint32_t dir = 0;
    float mag = 0;

    for(;;)
    {
        mag = stickMag.get()/100;   //make mag a scaler from 0-1.
        //Serial << "Original mag is: " << mag << endl;
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
            //Serial << "Moving North" << endl;
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
        
        //Serial << "Mag: " << mag << " Relative Speed: " << FL_relativeSpeed << " Max speed: " << max_Speed << endl;
        idealSpeed[0] = mag*FL_relativeSpeed*max_Speed;
        idealSpeed[1] = mag*BL_relativeSpeed*max_Speed;
        idealSpeed[2] = mag*FR_relativeSpeed*max_Speed;
        idealSpeed[3] = mag*BR_relativeSpeed*max_Speed;

        // Serial << "Ideal Speed (M1) is " << idealSpeed[0] << endl;
        // Serial << "Ideal Speed (M2) is " << idealSpeed[1] << endl;
        // Serial << "Ideal Speed (M3) is " << idealSpeed[2] << endl;
        // Serial << "Ideal Speed (M4) is " << idealSpeed[3] << endl;

        realSpeed[0] = enc0_RPS.get();
        realSpeed[1] = enc1_RPS.get();
        realSpeed[2] = enc2_RPS.get();
        realSpeed[3] = enc3_RPS.get();
        // Serial << "Real Speed (M1) is " << realSpeed[0] << endl;
        // Serial << "Real Speed (M2) is " << realSpeed[1] << endl;
        // Serial << "Real Speed (M3) is " << realSpeed[2] << endl;
        // Serial << "Real Speed (M4) is " << realSpeed[3] << endl;

        for (uint8_t n=0; n < 4; n++)
        {
            pwm[n] = (idealSpeed[n]-realSpeed[n])*P_gain;
            //Serial << n << "PWM_P is " << pwm[n] << endl;
           // integral_error[n] += (idealSpeed[n]-realSpeed[n])*(.005);  // MULTIPLY BY TIME?? dt
            integral_error[n] += (idealSpeed[n]-realSpeed[n]);  // MULTIPLY BY TIME?? dt
            deriv_error[n] += ((idealSpeed[n]-realSpeed[n])-(e_prior[n]));// ADDED BY DAN 
            //pwm[n] += integral_error[n]*I_gain;
            pwm[n] += (integral_error[n]*I_gain+deriv_error[n]*D_gain);
            
            //Serial << n << "PWM_I is " << integral_error[n]*I_gain << endl;
            if (pwm[n] > max_pwm)
            {
                pwm[n] = max_pwm;
            }
            e_prior[n] = idealSpeed[n] - realSpeed[n];
        }
        //Serial << "I_Error is " << integral_error[0] << endl;

        // Serial << "PWM is (M1) " << pwm[0] << endl;
        // Serial << "PWM is (M2) " << pwm[1] << endl;
        // Serial << "PWM is (M3) " << pwm[2] << endl;
        // Serial << "PWM is (M4) " << pwm[3] << endl;
        //Serial.println("PWM is: ");
        //Serial.println(pwm[0]);

        //Serial << pwm[0] << endl;
        FL_pwm.put(pwm[0]);
        BL_pwm.put(pwm[1]);
        FR_pwm.put(pwm[2]);
        BR_pwm.put(pwm[3]);

       vTaskDelay(5);
    }
}