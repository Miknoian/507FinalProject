#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Encoder.h>
#include "task_encoder.h"
#include <WiFi.h>
#include "shares.h"

//Encoder 0
const uint8_t INPUT1 = 32;
const uint8_t INPUT2 = 35;

//Encoder 1
const uint8_t INPUT3 = 10;
const uint8_t INPUT4 = 34;  // potential replacement for non-functional pin 1

//Encoder 2
const uint8_t INPUT5 = 23; //23, 26
const uint8_t INPUT6 = 26; // potential replacement for non-functional pin 6

//Encoder 3
const uint8_t INPUT7 = 16;
const uint8_t INPUT8 = 4;

void task_encoder (void* p_params)
{

    ESP32Encoder encoder0; 
    encoder0.attachFullQuad(INPUT1, INPUT2);
    encoder0.setCount(0);
    encoder0.resumeCount();

    ESP32Encoder encoder1;
    encoder1.attachFullQuad(INPUT3, INPUT4);
    encoder1.setCount(0);
    encoder1.resumeCount();

    ESP32Encoder encoder2; 
    encoder2.attachFullQuad(INPUT5, INPUT6);
    encoder2.setCount(0);
    encoder2.resumeCount();

    ESP32Encoder encoder3;
    encoder3.attachFullQuad(INPUT7, INPUT8);
    encoder3.setCount(0);
    encoder3.resumeCount();

    float enc0RotVel = 0;
    float enc1RotVel = 0;
    float enc2RotVel = 0;
    float enc3RotVel = 0;

    int32_t enc0PrevPos = 0;
    int32_t enc1PrevPos = 0;
    int32_t enc2PrevPos = 0;
    int32_t enc3PrevPos = 0;

    uint32_t previousTime = 0;
    uint32_t currentTime = 0;

    

    for(;;)
    {
        // Serial.print("enc0: ");
        // Serial.print(String((int32_t)encoder0.getCount()));
        // Serial.print(" enc1: ");
        // Serial.print(String((int32_t)encoder1.getCount()));
        // Serial.print(" enc2: ");
        // Serial.print(String((int32_t)encoder2.getCount()));
        // Serial.print(" enc3: ");
        // Serial.print(String((int32_t)encoder3.getCount()));
        // Serial << endl;


        previousTime = currentTime;
        currentTime = xTaskGetTickCount();

        // Serial.println("currentTime  ");
        // Serial.print(currentTime);
        // Serial.print("prevTime  ");
        // Serial.println(previousTime);
        
        
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

        // Serial.println("enc0: ");
        // Serial.print(String(enc0_RPS.get()));
        // Serial.print("   enc0 not share: ");
        // Serial.print(enc0RotVel);
        // Serial.print("   enc0 current pos: ");
        // Serial.print(encoder0.getCount());
        // Serial << endl;

        // Serial.print(" enc1: ");
        // Serial.print(String((int32_t)encoder1.getCount()));
        // Serial.print(" enc2: ");
        // Serial.print(String((int32_t)encoder2.getCount()));
        // Serial.print(" enc3: ");
        // Serial.print(String((int32_t)encoder3.getCount()));
        // Serial << endl;

        vTaskDelay(100);
    }
}