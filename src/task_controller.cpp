/** @file   controller.cpp
 *  @brief    Task for PID control loop that manages motor speeds based on reported encoder velocities 
 *  @details     This task takes inputs from the wifi task to set desired direction and speed, updates motor PWM using
 *              encoder velocities in PID control loop
 *  @author Joshua Hoye
 *  @date   11/30/2021
 */
 


#include <Arduino.h>
#include <PrintStream.h>
#include "task_controller.h"
#include "shares.h"


/**
 * @brief Function to run controller task
 * @details Controller function takes a direction input and creates a scaler for the desired speed on each motor. This will 
 * then be multiplied by the desired overall nominal speed to get the nominal speed for each motor. This speed goal is used in the 
 * PID control loop as a target. Encoder feedback is used to correct PWM signal.
 */
void task_controller (void* p_params)
{   
    // A scaler that represents the speed relative to the other motors.
    float FL_relativeSpeed = 0;
    float BL_relativeSpeed = 0;
    float FR_relativeSpeed = 0;
    float BR_relativeSpeed = 0;

    // speed target based on user input
    double idealSpeed[] = {0,0,0,0};

    // current motor speeds
    float realSpeed[] = {0,0,0,0};

    // integral error for each motor
    int32_t integral_error[] = {0,0,0,0};

    // PWM for each motor
    int32_t pwm[] = {0,0,0,0};

    // derivative error for each motor
    int32_t deriv_error[] = {0,0,0,0};

    // previous error for each motor
    int32_t e_prior[] = {0,0,0,0};

    // gains found through physical testing
    float P_gain = 3.5;
    float I_gain = .1;
    float D_gain= .001;

    const uint32_t max_pwm = 255;     //desired max PWM signal used to clamp outputs
    const int32_t max_Speed = 30;     // desired max RPM used to scale output
    
    uint32_t dir = 0;   // shared motor direction
    float mag = 0;      // shared motor PWM magnitude

    for(;;)
    {
        mag = stickMag.get()/100.0;   //make mag a scaler from 0-1.
        dir = stickAngle.get();     // get user joystick input angle

        // for mechanum wheels, each quadrant of the joystick corresponds to a slightly different control method wheels
        // For each, two diagonal wheels maintain the max scalled speed, while the two other diagonal wheels scale with direction
        // this logic before the control loop producing correctly scalled desired speeds for the control loop to work with

        //If panning E / NE
        if (dir >= 0 && dir < 90)   //These if statements produce the relative speed of each motor
        {
            FL_relativeSpeed = -1.0 + 2.0*(dir/90.0);  
            FR_relativeSpeed = 1;
            BL_relativeSpeed = 1;
            BR_relativeSpeed = -1.0 + 2.0*(dir/90.0);
            Serial.println("Loop1");
        }

        //If panning N/NW
        if (dir-90 >= 0 && dir-90 < 90)
        {
            //Serial << "Moving North" << endl;
            FL_relativeSpeed = 1;
            FR_relativeSpeed = 1.0-2.0*((dir-90.0)/90.0);
            BL_relativeSpeed = 1.0-2.0*((dir-90.0)/90.0);
            BR_relativeSpeed = 1;
            Serial.println("Loop2");
        }

        //If panning W/SW
        if (dir-180 >= 0 && dir-180 < 90)
        {
            FL_relativeSpeed = 1.0-2.0*((dir-180.0)/90.0);
            FR_relativeSpeed = -1;
            BL_relativeSpeed = -1;
            BR_relativeSpeed = 1.0-2.0*((dir-180.0)/90.0);
            Serial.println("Loop3");
        }

        //If panning S/SE
        if (dir-270 >= 0 && dir-270 < 90)
        {
            FL_relativeSpeed = -1;
            FR_relativeSpeed = -1.0 + 2.0*((dir-270.0)/90.0);
            BL_relativeSpeed = -1.0 + 2.0*((dir-270.0)/90.0);
            BR_relativeSpeed = -1;
            Serial.println("Loop4");
        }
        
        //desired wheel speed multiplied by joystick magnitude input

        idealSpeed[0] = mag*FL_relativeSpeed*max_Speed;
        idealSpeed[1] = mag*BL_relativeSpeed*max_Speed;
        idealSpeed[2] = mag*FR_relativeSpeed*max_Speed;
        idealSpeed[3] = mag*BR_relativeSpeed*max_Speed;

        //get encoder velocities for control loop

        realSpeed[0] = enc0_RPS.get();
        realSpeed[1] = enc1_RPS.get();
        realSpeed[2] = enc2_RPS.get();
        realSpeed[3] = enc3_RPS.get();

        for (uint8_t n=0; n < 4; n++)
        {
            pwm[n] = (idealSpeed[n]-realSpeed[n])*P_gain; // p control based on speed error
            integral_error[n] += (idealSpeed[n]-realSpeed[n])*(.005);  // multiply by time step for integral control using previous errors
            deriv_error[n] += ((idealSpeed[n]-realSpeed[n])-(e_prior[n])); // derivative control using prior error
            pwm[n] += (integral_error[n]*I_gain+deriv_error[n]*D_gain); // combination of all error for PWM signal
            
            // clamp logic for max PWM
            if (pwm[n] > max_pwm)    
            {
                pwm[n] = max_pwm;
            }
            e_prior[n] = idealSpeed[n] - realSpeed[n];
        }

        // send updated PWM to motor tasks
        FL_pwm.put(pwm[0]);
        BL_pwm.put(pwm[1]);
        FR_pwm.put(pwm[2]);
        BR_pwm.put(pwm[3]);

        
        //Set the direction share based on the relative speed
        if (FL_relativeSpeed > 0)
        {
            FL_dir.put(1); // Spin motor forward
        }
        else
        {
            FL_dir.put(0); // Spin motor backward
        }

        //Set the direction share based on the relative speed
        if (BL_relativeSpeed > 0)
        {
            BL_dir.put(1); // Spin motor forward
        }
        else
        {
            BL_dir.put(0); // Spin motor backward
        }

        //Set the direction share based on the relative speed
        if (FR_relativeSpeed > 0)
        {
            FR_dir.put(1); // Spin motor forward
        }
        else
        {
            FR_dir.put(0); // Spin motor backward
        }

        //Set the direction share based on the relative speed
        if (BR_relativeSpeed > 0)
        {
            BR_dir.put(1); // Spin motor forward
        }
        else
        {
            BR_dir.put(0); // Spin motor backward
        }
       vTaskDelay(5);  // 10 ms task period
    }
}