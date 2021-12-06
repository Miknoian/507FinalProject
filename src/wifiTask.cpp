/** @file wifiTask.cpp
 * @brief Function to handle all WiFi items
 * @details Function sets up ESP32 as a WiFi access point and then scans for HTTP requests. It reads the HTTP
 * request and stores it in a string. Once a carriage return has been read (the end of the request) it stops building
 * up the string and searches it for data. It reads both the radius (velocity) and angle (orientation) from the URL
 * and places them into shared variables
 * @author Daniel Freeman
 * @date 05-Dec-2021
*/

#include <Arduino.h>
#include <PrintStream.h>
#include <WiFi.h>
#include "wifiTask.h"
#include "shares.h"

/** @brief Function to search for connections and set shared variables
 * @details Function sets up ESP32 as a WiFi access point and then scans for HTTP requests. It reads the HTTP
 * request and stores it in a string. Once a carriage return has been read (the end of the request) it stops building
 * up the string and searches it for data. It reads both the radius (velocity) and angle (orientation) from the URL
 * and places them into shared variables
*/
void wifiTask(void* p_params)
{
    const char *ssid = "yourAP";    /// Arbitrary ssid to connect to on device
    WiFiServer server(80);          // Set web server at port 80
    String header;                  /// String to store the HTTP request
    Serial.println();                                 // Print a blank line to serial monitor
    Serial.println("Configuring access point...");    // Print statement
    WiFi.softAP(ssid);                                // Set ESP to be a soft access point with specified SSID
    IPAddress myIP = WiFi.softAPIP();                 /// Get IP address of access point (the ESP32)
    Serial.print("AP IP address: ");                  // Print access point
    Serial.println(myIP);                             // Print access point
    server.begin();                                   // Blank line
    Serial.println("Server started");                 // Print statement
    String PWM;                                     /// PWM String from http request
    String angle;                                   /// Angle String from http request
    String pwmOne;                                  // First character in PWM string
    String pwmTwo;                                  /// Second character in PWM string
    String thetaOne;                                /// First character in angle string
    String thetaTwo;                                /// Second character in angle string
    String thetaThree;                              /// Third character in angle string
    
    for(;;)
    {   
        const char* host = "192.168.4.1";               /// The IP address of our ESP32
        WiFiClient client = server.available();         /// Object for availability of server
        if (client)                                     // if a new client connects
        {  
            Serial.print("Connected");                         
            String currentLine = "";                    /// 'currentLine' stores the current line of the request
            while (client.connected())                  // While client is connected to access point
            {
                if (client.available())                 // Check if there are unread characters from the request
                {           
                    char c = client.read();             /// c stores the current character we are reading
                    if (c != '\r')                      // If we read anything but a carriage return
                    {  
                        currentLine += c;               // add it to the end of the currentLine
                    }
                    if (c == '\r')                      // If we get a carriage return (end of request)
                    {
                        pwmOne = currentLine[5];        //5th Character in header (first number in PWM)
                        pwmTwo = currentLine[6];        //6th Character in header (second number in PWM)
                        thetaOne = currentLine[7];
                        thetaTwo = currentLine[8];
                        thetaThree = currentLine[9]; 
                        angle = thetaOne+thetaTwo+thetaThree;                       
                        PWM = pwmOne+pwmTwo;                                        
                        stickMag.put(PWM.toInt());      // Put the integer PWM into a shared variable
                        stickAngle.put(angle.toInt());  // Put the integer angle into a shared variable
                        break;                          // Return from loop
                    }
                } 
            } 
        } 
        vTaskDelay(10);                                 // Delay 5ms in task
    }
}
