#include <WiFi.h>
#include "WiFi_thing.h"

const char *ssid = "yourAP";    // Arbitrary ssid to connect to on device
WiFiServer server(80);          // Set web server at port 80
String header;                  // Storing the HTTP request

WiFi_thing::WiFi_thing(void)    // Constructor
{
}
/** @brief Function to set up ESP as WiFi access point
*/
void WiFi_thing::setup()        
{
  Serial.begin(115200);                             // Set baud rate for serial communication
  Serial.println();                                 // Print a blank line to serial monitor
  Serial.println("Configuring access point...");    // Print statement
  WiFi.softAP(ssid);                                // Set ESP to be a soft access point with specified SSID
  IPAddress myIP = WiFi.softAPIP();                 // Get IP address of access point
  Serial.print("AP IP address: ");                  // Print access point
  Serial.println(myIP);                             // Print access point
  server.begin();                                   // Blank line
  Serial.println("Server started");                 // Print statement
}
/** @brief Function to search for connections and return values
 * @details 
 * @returns
*/
uint16_t WiFi_thing::loop() 
{  
    const char* host = "192.168.4.1";               // The address we will return things to, which is our IP address
    const char* streamId   = "....................";// Not sure
    const char* privateKey = "....................";// Not sure
    WiFiClient client = server.available();         // listen for incoming clients
    String pwmOne;
    String pwmTwo;
    String thetaOne;
    String thetaTwo;
    String thetaThree;
    if (client)                                     // if a new client connects
    {                             
        String currentLine = "";                    // 'currentLine' stores the current line of the request
        while (client.connected())                  // While client is connected to access point
        {
            if (client.available())                 // check if there are unread characters from the request
            {          
                char c = client.read();             // c stores the current character we are reading
                Serial.write(c);
                if (c != '\r')
                {  
                    currentLine += c;   // add it to the end of the currentLine
                }
                // Testing 11/30
                if (c == '\r') // If we get a carriage return (end of request)
                {
                    pwmOne = currentLine[5]; // 5th Character in header (first number in PWM)
                    pwmTwo = currentLine[6]; // 6th Character in header (second number in PWM)
                    thetaOne = currentLine[7];
                    thetaTwo = currentLine[8];
                    thetaThree = currentLine[9];  
                    //Serial.println(digitOne+digitTwo);
                    PWM = pwmOne+pwmTwo; // Total PWM as a string of characters
                    angle = thetaOne+thetaTwo+thetaThree;
                    uint16_t r;
                    uint16_t theta; 
                    r = PWM.toInt(); // Convert to integer
                    theta = angle.toInt();
                    Serial.println("PWM signal is: ");
                    Serial.println(r);
                    Serial.println("Angle signal is: ");
                    Serial.println(theta);
                    data[1] = r;
                    data[2] = theta;
                    return data;
                }
                // Below section sets the value of variables defined in class (.h) to different values depending
                // on the ending of the http request
                if (currentLine.endsWith("GET /START")) 
                {
                    mot_enab = 1;
                    return mot_enab;
                }
                if (currentLine.endsWith("GET /END")) 
                {
                    mot_enab = 0;
                    return mot_enab;
                }   
            } 
        } 
    } 
    return motor; // If there is no client, return anyway (fixes "control reaches end of non-void function")
}
