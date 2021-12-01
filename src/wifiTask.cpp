/** @file wifiTask.cpp
 * @brief Function to handle all WiFi items
 * @details Function sets up ESP32 as a WiFi access point and then scans for HTTP requests. It reads the HTTP
 * request and stores it in a string. Depending on the string, the function will do different things. The function returns
 * a five digit number (signal), of which the first two digits are the radius of movement as a percentage and the last
 * three are the angle of movement on the joypad.
 * @returns signal An integer value containing data of radius and angle of movement
*/

#include <WiFi.h>
#include "wifiTask.h"
#include "shares.h"

/** @brief Function to search for connections and return values
 * @details 
 * @returns
*/
void wifiTask(void* p_params)
{
    const char *ssid = "yourAP";    // Arbitrary ssid to connect to on device
    WiFiServer server(80);          // Set web server at port 80
    String header;                  // Storing the HTTP request
    Serial.begin(115200);                             // Set baud rate for serial communication
    Serial.println();                                 // Print a blank line to serial monitor
    Serial.println("Configuring access point...");    // Print statement
    WiFi.softAP(ssid);                                // Set ESP to be a soft access point with specified SSID
    IPAddress myIP = WiFi.softAPIP();                 // Get IP address of access point
    Serial.print("AP IP address: ");                  // Print access point
    Serial.println(myIP);                             // Print access point
    server.begin();                                   // Blank line
    Serial.println("Server started");                 // Print statement
    uint32_t _signal = 0;
    for(;;)
    {
        //const char* host = "192.168.4.1";           // The address we will return things to, which is our IP address
        //const char* streamId   = "....................";// Not sure
        //const char* privateKey = "....................";// Not sure
        WiFiClient client = server.available();         // listen for incoming clients
        String PWM;                                     // PWM String from http
        String angle;                                   // Angle String from http
        String pwmOne;                                  // First character in PWM string
        String pwmTwo;                                  // Second character in PWM string
        String thetaOne;                                // First character in angle string
        String thetaTwo;                                // Second character in angle string
        String thetaThree;                              // Third character in angle string
        if (client)                                     // if a new client connects
        {                             
            String currentLine = "";                    // 'currentLine' stores the current line of the request
            while (client.connected())                  // While client is connected to access point
            {
                if (client.available())                 // check if there are unread characters from the request
                {          
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
                        angle = thetaOne+thetaTwo+thetaThree; // Total angle as a string of characters
                        PWM = pwmOne+pwmTwo; // Total PWM as a string of characters
                        String str_signal = pwmOne+pwmTwo+thetaOne+thetaTwo+thetaThree; // Total signal as a string
                        _signal = str_signal.toInt(); // Convert to integer
                        Serial.println("PWM signal is: ");
                        Serial.println(PWM);
                        Serial.println("Angle signal is: ");
                        Serial.println(angle);
                        signal.put(_signal);
                    }
                } 
            } 
        } 
        vTaskDelay(5); // Delay 5ms in task
        }
}
