#include <Arduino.h>
#include <WiFi.h>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

/** @brief   Class to handle WiFi
 *  @details This class handles all WiFi stuff. The class creates several variables that are changed depending on 
 *           http requests. The class contains a function that set up ESP as an access point and a function that 
 *           searches for requests and changes variable values based on those requests.
 */
class WiFi_thing
{
    public:
        bool motor = 0; ///< Variable for controlling motor speed
        bool mot_enab = 0; ///< Variable for enabling and disabling motor
        bool feedback = 0; ///< Variable for providing feedback on the motor
        String PWM; 
        String angle;
        struct array
        {
            uint16_t data[2];
        };
        WiFi_thing(void); // Constructor
        void setup(void); 
        uint16_t loop(void);
};