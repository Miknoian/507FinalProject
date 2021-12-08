/** @file   class_motor.cpp
 *  @brief Class for motors
 *  @details This class contains a constructor which sets up pins and PWM channels, and then a function to run the motors. Depending on the direction, the PWM
 * channels will change because of the direction change.
 *  @author Joshua Hoye
 *  @date   11/30/2021
 */

#include <Arduino.h>
#include <PrintStream.h>
#include "class_motor.h"

/** @brief      Constructor for brushed motor object.   
 *  @details    This constructor creates a motor object with its specified control pins and timing channels.
 */
Motor::Motor (uint8_t M_IN1, uint8_t M_IN2, uint8_t PWM_1, uint8_t PWM_2)
{
    //Save all inputs for use in functions
    MOTOR_IN1 = M_IN1; /// Pin 1 for motor
    MOTOR_IN2 = M_IN2; /// Pin 2 for motor
    PWM_Ch1 = PWM_1; /// PWM Channel 1
    PWM_Ch2 = PWM_2; /// PWM Channel 2
}

/** @brief      This function sends the PWM signal to the motor.   
 *  @details    This function writes the given PWM signal to the appropriate timing channel based on the direction.  
 */
void Motor::run (uint8_t PWM, bool dir)
{
    //forward
    if (dir) 
    {
        ledcWrite(PWM_Ch1, 0);
        ledcWrite(PWM_Ch2, PWM);
        //Serial << "PWM: " << PWM << " forward on channel " << PWM_Ch2 << endl;
    }
    else

    //backward 
    {
        ledcWrite(PWM_Ch2, 0);
        ledcWrite(PWM_Ch1, PWM);
        //Serial << "PWM: " << PWM << " backward on channel " << PWM_Ch1 << endl;
    }
}


