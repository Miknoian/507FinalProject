#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Encoder.h>
#include "task_encoder.h"
#include <WiFi.h>
#include "shares.h"

const TickType_t ENCODER_PERIOD = 5;

const uint8_t INPUT1 = 32;
const uint8_t INPUT2 = 35; // doesnt work
//const uint8_t INPUT2 = ;

const uint8_t INPUT3 = 10;
const uint8_t INPUT4 = 15; // potential replacement for non-functional pin 6

const uint8_t INPUT5 = 16;
const uint8_t INPUT6 = 4;

const uint8_t INPUT7 = 23;
const uint8_t INPUT8 = 3;  // potential replacement for non-functional pin 1

void task_encoder (void* p_params)
{
    // Serial.println("wifi setup start");
    // delay(2000);
    // WiFi.mode(WIFI_AP);
    // WiFi.disconnect();
    // delay(2000);
    // Serial.println("wifi setup complete");

    ESP32Encoder encoder1; 
    encoder1.attachFullQuad(INPUT1, INPUT2);
    encoder1.setCount(0);
    encoder1.resumeCount();

    ESP32Encoder encoder2;
    encoder2.attachFullQuad(INPUT3, INPUT4);
    encoder2.setCount(0);
    encoder2.resumeCount();

    ESP32Encoder encoder3; 
    encoder3.attachFullQuad(INPUT5, INPUT6);
    encoder3.setCount(0);
    encoder3.resumeCount();

    ESP32Encoder encoder4;
    encoder4.attachFullQuad(INPUT7, INPUT8);
    encoder4.setCount(0);
    encoder4.resumeCount();

    TickType_t xLastWakeTime = xTaskGetTickCount();

    float enc1RotVel = 0;
    float enc2RotVel = 0;
    float enc3RotVel = 0;
    float enc4RotVel = 0;

    int32_t enc1PrevPos = 0;
    int32_t enc2PrevPos = 0;
    int32_t enc3PrevPos = 0;
    int32_t enc4PrevPos = 0;

    uint32_t previousTime = 0;
    uint32_t currentTime = 0;

    for(;;)
    {
        // Serial.print("Enc1: ");
        // Serial.print(String((int32_t)encoder1.getCount()));
        // Serial.print(" Enc2: ");
        // Serial.print(String((int32_t)encoder2.getCount()));
        // Serial.print(" Enc3: ");
        // Serial.print(String((int32_t)encoder3.getCount()));
        // Serial.print(" Enc4: ");
        // Serial.print(String((int32_t)encoder4.getCount()));
        // Serial << endl;

        previousTime = currentTime;
        currentTime = xTaskGetTickCount();
        
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

        // Serial.println(enc1RotVel);

        vTaskDelayUntil (&xLastWakeTime, ENCODER_PERIOD);
    }
}