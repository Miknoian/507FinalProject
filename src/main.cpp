#include <Arduino.h>
#include <PrintStream.h>
#include "task_encoder.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "shares.h"
#include "wifiTask.h"
// sneed

Share<int32_t> enc1_RPS ("sneed1");
Share<int32_t> enc2_RPS ("sneed2");
Share<int32_t> enc3_RPS ("sneed3");
Share<int32_t> enc4_RPS ("sneed4");
Share<uint32_t> signal  ("sneed5");

void setup() 
{
    Serial.begin (115200);
    delay (2000);
    xTaskCreate (wifiTask,
                "WIFI",
                8192,
                NULL,
                1,
                NULL);
    xTaskCreate (task_encoder,
                 "ENC",                           // Task name for printouts
                 8192,                            // Stack size
                 NULL,                            // Parameters for task fn.
                 1,                               // Priority
                 NULL);                           // Task handle

}

void loop() {
  // put your main code here, to run repeatedly:
}