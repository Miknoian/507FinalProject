/** @file wifiTask.cpp
 * @brief Function to handle all WiFi items
 * @details Function sets up ESP32 as a WiFi access point and then scans for HTTP requests. It reads the HTTP
 * request and stores it in a string. The string contains PWM and angle data. This data is extracted and put into shared variables.
*/

#include <Arduino.h>
#include <PrintStream.h>
#include <WiFi.h>
#include "wifiTask.h"
#include "shares.h"

/** @brief Function to search for connections and return values
*/
void wifiTask(void* p_params)
{
    const char *ssid = "yourAP";    /// SSID name for device
    WiFiServer server(80);          // Set web server at port 80
    String header;                  /// String to store the HTTP request
    Serial.println();                                 // Print a blank line to serial monitor
    Serial.println("Configuring access point...");    // Print statement
    WiFi.softAP(ssid);                                // Set ESP to be a soft access point with specified SSID
    IPAddress myIP = WiFi.softAPIP();                 /// IP address of our device, the access point
    Serial.print("AP IP address: ");                  // Print access point
    Serial.println(myIP);                             // Print access point
    server.begin();                                   // Blank line
    Serial.println("Server started");                 // Print statement
    uint32_t _signal = 0;                           // Total signal (for use in this file)
    String PWM;                                     /// PWM String from http
    String angle;                                   /// Angle String from http
    String pwmOne;                                  /// First character in PWM string
    String pwmTwo;                                  /// Second character in PWM string
    String thetaOne;                                /// First character in angle string
    String thetaTwo;                                /// Second character in angle string
    String thetaThree;                              /// Third character in angle string
    
    for(;;)
    {   
        const char* host = "192.168.4.1";           // The address we will return things to, which is our IP address
        const char* streamId   = "....................";// Not sure
        const char* privateKey = "....................";// Not sure
        WiFiClient client = server.available();         // listen for incoming clients
        if (client)                                     // if a new client connects
        {  
            Serial.print("Connected");                         
            String currentLine = "";                    // 'currentLine' stores the current line of the request
            while (client.connected())                  // While client is connected to access point
            {
                //Serial.println("Client.available is: ");
                // Serial.println(client.available());
                if (client.available())                 // check if there are unread characters from the request
                {           
                    //Serial.print("If client available loop");
                    char c = client.read();             // c stores the current character we are reading
                    Serial.write(c);
                    if (c != '\r')                      // If anything but a carriage return
                    {  
                        currentLine += c;               // add it to the end of the currentLine
                    }
                    if (c == '\r') // If we get a carriage return (end of request)
                    {
                        pwmOne = currentLine[5];  //5th Character in header (first number in PWM)
                        pwmTwo = currentLine[6];  //6th Character in header (second number in PWM)
                        thetaOne = currentLine[7];
                        thetaTwo = currentLine[8];
                        thetaThree = currentLine[9]; 
                        // Serial.println("currentLine[5] is: ");
                        // Serial.println(currentLine[5]); 
                        // Serial.println("currentLine[6] is: ");
                        // Serial.println(currentLine[6]); 
                        // Serial.println("currentLine[7] is: ");
                        // Serial.println(currentLine[7]); 
                        // Serial.println("currentLine[8] is: ");
                        // Serial.println(currentLine[8]); 
                        // Serial.println("currentLine[9] is: ");
                        // Serial.println(currentLine[9]); 
                        angle = thetaOne+thetaTwo+thetaThree;                       // Total angle as a string of characters
                        PWM = pwmOne+pwmTwo;                                        // Total PWM as a string of characters
                        //Serial.println("Angle is: ");
                        //Serial.println(angle.toInt());
                        // Serial.println("Mag is: ");
                        // Serial.println(PWM.toInt());
                        stickAngle.put(angle.toInt());
                        stickMag.put(PWM.toInt());
                        
                        //Serial.println(stickAngle.get());
                        break;
                    }
                } 
            } 
        } 
        vTaskDelay(5); // Delay 5ms in task
        }
}
