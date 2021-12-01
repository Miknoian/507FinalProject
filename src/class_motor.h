/** @file   class_motor.h
 * 
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
    /// Stuffs

    uint8_t MOTOR_IN1; 
    uint8_t MOTOR_IN2;
    uint8_t PWM_Ch1;
    uint8_t PWM_Ch2;

public:
    // Constructor which is given the pins for IN1 and IN2, and the desired channels for PWM.
    Motor (uint8_t MOTOR_IN1, uint8_t MOTOR_IN2, uint8_t PWM_Ch1, uint8_t PWM_Ch2);

    void run (uint8_t PWM, bool direction);                       // Set PWM for motor
};


