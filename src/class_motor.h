/** @file   class_motor.h
 *  @brief Header file for motor class
 *  @author Joshua Hoye
 *  @date   11/30/2021
 */

/** @brief      A class used for creating motor brushed motor objects.
 *  @details    This class allows for creating a motor object with specified pins and pwm channels, and provides functions to send
 *              desired PWM and direction. 
 */
class Motor
{
    protected:


        uint8_t MOTOR_IN1; // Pin 1 for motor
        uint8_t MOTOR_IN2; // Pin 2 for motor
        uint8_t PWM_Ch1; // Channel 1 for PWM
        uint8_t PWM_Ch2; // Channel 2 for PWM

    public:
        // Constructor which is given the pins for IN1 and IN2, and the desired channels for PWM.
        Motor (uint8_t MOTOR_IN1, uint8_t MOTOR_IN2, uint8_t PWM_Ch1, uint8_t PWM_Ch2);

        void run (uint8_t PWM, bool direction);                       // Set PWM for motor
};


