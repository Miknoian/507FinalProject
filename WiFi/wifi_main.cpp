#include "WiFi_thing.h"
#include <Arduino.h>

WiFi_thing WeeFee; // Create object of WiFi_thing named WeeFee (avoids conflicting declaration when naming it "WiFi")

void setup()
{
    Serial.begin(115200);   // Cereal coms
    delay(2000);            // Delay for serial
    WeeFee.setup();         // Run setup function of object WiFi
}

void loop()
{
    WeeFee.loop();
    //Serial.println(WeeFee.loop());  // Run loop function of object WiFi and print whatever it says
    if (WeeFee.mot_enab == 1)       // If start is pushed
    {   
        pinMode(12, OUTPUT);        // Set GPIO 12 to output mode
        if (WeeFee.motor == 1)      // If motor go
        {
            Serial.write("Motor should be spinning");
            digitalWrite(12,HIGH);   // Set pin high
        }
        if (WeeFee.motor == 0)      // If motor no
        {
            digitalWrite(12,LOW);    // Set pin low
        }
    }
}
        
