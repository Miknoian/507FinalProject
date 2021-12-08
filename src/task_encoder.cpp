/** @file task_encoder.cpp
 * @brief Function to handle all encoder items
 * @details Function sets up pins for use as channels 1 and 2 for each of the four encoders. It then creates objects for each encoder and assigns them to 
 * pins. For each encoder, the count is intitialized to zero before starting to count. An algorithm is used to convert the encoder ticks to radians per second
* @author Mark Iknoian
*/
#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Encoder.h>
#include "task_encoder.h"
#include <WiFi.h>
#include "shares.h"

//Encoder 0
const uint8_t INPUT1 = 32;                      /// Pin for encoder 0 channel 1
const uint8_t INPUT2 = 35;                      /// Pin for encoder 0 channel 2

//Encoder 1
const uint8_t INPUT3 = 10;                      /// Pin for encoder 1 channel 1
const uint8_t INPUT4 = 34;                      /// Pin for encoder 1 channel 2

//Encoder 2
const uint8_t INPUT5 = 23;                      /// Pin for encoder 2 channel 1
const uint8_t INPUT6 = 26;                      /// Pin for encoder 2 channel 2

//Encoder 3
const uint8_t INPUT7 = 16;                      /// Pin for encoder 3 channel 1
const uint8_t INPUT8 = 4;                       /// Pin for encoder 3 channel 2

/// @brief Function to obtain usable data from encoders and put into shared variables
void task_encoder (void* p_params)
{

    ESP32Encoder encoder0;                      /// Encoder 0 object of class ESP32Encoder
    encoder0.attachFullQuad(INPUT1, INPUT2);
    encoder0.setCount(0);
    encoder0.resumeCount();

    ESP32Encoder encoder1;                      /// Encoder 1 object of class ESP32Encoder
    encoder1.attachFullQuad(INPUT3, INPUT4);
    encoder1.setCount(0);
    encoder1.resumeCount();

    ESP32Encoder encoder2;                      /// Encoder 2 object of class ESP32Encoder
    encoder2.attachFullQuad(INPUT5, INPUT6);
    encoder2.setCount(0);
    encoder2.resumeCount();

    ESP32Encoder encoder3;                      /// Encoder 3 object of class ESP32Encoder
    encoder3.attachFullQuad(INPUT7, INPUT8);
    encoder3.setCount(0);
    encoder3.resumeCount();

    float enc0RotVel = 0;                       /// Rotational velocity of encoder 0, in rad/s
    float enc1RotVel = 0;                       /// Rotational velocity of encoder 1, in rad/s  
    float enc2RotVel = 0;                       /// Rotational velocity of encoder 2, in rad/s
    float enc3RotVel = 0;                       /// Rotational velocity of encoder 3, in rad/s

    int32_t enc0PrevPos = 0;                    /// Previous position of encoder 0, in ticks
    int32_t enc1PrevPos = 0;                    /// Previous position of encoder 1, in ticks
    int32_t enc2PrevPos = 0;                    /// Previous position of encoder 2, in ticks
    int32_t enc3PrevPos = 0;                    /// Previous position of encoder 3, in ticks

    uint32_t previousTime = 0;                  /// Previous timestamp in ms
    uint32_t currentTime = 0;                   /// Previous timestamp in ms

    

    for(;;)
    {
        previousTime = currentTime;
        currentTime = xTaskGetTickCount();

        enc0RotVel = ((encoder0.getCount()-enc0PrevPos)*1000*2*3.1416)/((currentTime-previousTime)*230.70);
        enc0PrevPos = encoder0.getCount();
        enc0_RPS.put(enc0RotVel);

        enc1RotVel = ((encoder1.getCount()-enc1PrevPos)*1000*2*3.1416)/((currentTime-previousTime)*230.70);
        enc1PrevPos = encoder1.getCount();
        enc1_RPS.put(enc1RotVel);

        enc2RotVel = ((encoder2.getCount()-enc2PrevPos)*1000*2*3.1416)/((currentTime-previousTime)*230.70);
        enc2PrevPos = encoder2.getCount();
        enc2_RPS.put(enc2RotVel);

        enc3RotVel = ((encoder3.getCount()-enc3PrevPos)*1000*2*3.1416)/((currentTime-previousTime)*230.70);
        enc3PrevPos = encoder3.getCount();
        enc3_RPS.put(enc3RotVel);

        vTaskDelay(100);
    }
}