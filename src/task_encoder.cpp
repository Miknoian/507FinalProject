/** @file task_encoder.cpp
 * @brief Function to handle all encoder items
 * @details Function sets up encoders using specified pins. 
 * @author Mark Iknoian
 * @date 05-Dec-2021
*/
#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Encoder.h>
#include "task_encoder.h"
#include <WiFi.h>
#include "shares.h"

const TickType_t ENCODER_PERIOD = 5;            /// Period for encoders in milliseconds

const uint8_t INPUT1 = 32;                      /// Pin for encoder 1 channel 1
const uint8_t INPUT2 = 35;                      /// Pin for encoder 1 channel 2

const uint8_t INPUT3 = 10;                      /// Pin for encoder 2 channel 1
const uint8_t INPUT4 = 34; // potential replacement for non-functional pin 6

const uint8_t INPUT5 = 16;                      /// Pin for encoder 3 channel 1
const uint8_t INPUT6 = 4;                       /// Pin for encoder 3 channel 2

const uint8_t INPUT7 = 23;                      /// Pin for encoder 4 channel 1
const uint8_t INPUT8 = 26;  // potential replacement for non-functional pin 1

/// @brief Function to obtain data from encoders
void task_encoder (void* p_params)
{
    ESP32Encoder encoder1;                      /// Encoder 1 object of class ESP32Encoder
    encoder1.attachFullQuad(INPUT1, INPUT2);    // Set pins
    encoder1.setCount(0);                       // Set initial count
    encoder1.resumeCount();                     // Resume count

    ESP32Encoder encoder2;                      /// Encoder 2 object of class ESP32Encoder
    encoder2.attachFullQuad(INPUT3, INPUT4);    // Set pins
    encoder2.setCount(0);                       // Set initial count
    encoder2.resumeCount();                     // Resume count

    ESP32Encoder encoder3;                      /// Encoder 3 object of class ESP32Encoder
    encoder3.attachFullQuad(INPUT5, INPUT6);    // Set pins
    encoder3.setCount(0);                       // Set initial count
    encoder3.resumeCount();                     // Resume count

    ESP32Encoder encoder4;                      /// Encoder 4 object of class ESP32Encoder
    encoder4.attachFullQuad(INPUT7, INPUT8);    // Set pins
    encoder4.setCount(0);                       // Set initial count
    encoder4.resumeCount();                     // Resume count

    TickType_t xLastWakeTime = xTaskGetTickCount();     /// The last tick of the encoder

    float enc1RotVel = 0;   /// Initial rotational velocity of encoder 1 
    float enc2RotVel = 0;   /// Initial rotational velocity of encoder 2
    float enc3RotVel = 0;   /// Initial rotational velocity of encoder 3 
    float enc4RotVel = 0;   /// Initial rotational velocity of encoder 4 

    int32_t enc1PrevPos = 0;    /// Previous position of encoder 1 
    int32_t enc2PrevPos = 0;    /// Previous position of encoder 2 
    int32_t enc3PrevPos = 0;    /// Previous position of encoder 3  
    int32_t enc4PrevPos = 0;    /// Previous position of encoder 4 

    uint32_t previousTime = 0;  /// Previous time counter 
    uint32_t currentTime = 0;   /// Current time counter 

    for(;;)
    {
        previousTime = currentTime;         // Set the previous timestamp to the current time
        currentTime = xTaskGetTickCount();  // Get the current time
        
        enc1RotVel = ((encoder1.getCount()-enc1PrevPos)*1000*2*3.1416)/((currentTime-previousTime)*230.70);
        enc1PrevPos = encoder1.getCount();
        enc1_RPS.put(enc1RotVel);

        enc2RotVel = ((encoder2.getCount()-enc2PrevPos)*1000*2*3.1416)/((currentTime-previousTime)*230.70);
        enc2PrevPos = encoder2.getCount();
        enc2_RPS.put(enc2RotVel);

        enc3RotVel = ((encoder3.getCount()-enc3PrevPos)*1000*2*3.1416)/((currentTime-previousTime)*230.70);
        enc3PrevPos = encoder3.getCount();
        enc3_RPS.put(enc3RotVel);

        enc4RotVel = ((encoder4.getCount()-enc4PrevPos)*1000*2*3.1416)/((currentTime-previousTime)*230.70);
        enc4PrevPos = encoder4.getCount();
        enc4_RPS.put(enc4RotVel);

        vTaskDelayUntil (&xLastWakeTime, ENCODER_PERIOD);
    }
}