#include <Arduino.h>
#include <PrintStream.h>
#include "task_encoder.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "shares.h"
#include "wifiTask.h"
#include "task_motor.h"             // Header for motor driver module
#include "task_controller.h"        // Header for motor controller

// sneed

Share<int32_t> enc1_RPS ("sneed1");
Share<int32_t> enc2_RPS ("sneed2");
Share<int32_t> enc3_RPS ("sneed3");
Share<int32_t> enc4_RPS ("sneed4");

Share<uint32_t> signal  ("sneed5");

Share<uint8_t> FL_mag   ("sneed6");
Share<uint8_t> FR_mag   ("sneed7");
Share<uint8_t> BL_mag   ("sneed8");
Share<uint8_t> BR_mag   ("sneed9");

Share<bool> FL_dir   ("sneed10");
Share<bool> FR_dir   ("sneed11");
Share<bool> BL_dir   ("sneed12");
Share<bool> BR_dir   ("sneed13");

void setup() 
{
    //The following pins are used to control the motors. They must be set here because they cause a reboot loop when in a task.
    const uint16_t PWM_Freq = 1000;
    const uint8_t PWM_Res = 8;

    ledcAttachPin(33, 0);
    ledcAttachPin(25, 1);

    ledcAttachPin(14, 2);
    ledcAttachPin(27, 3);

    ledcAttachPin(18, 4);
    ledcAttachPin(19, 5);

    ledcAttachPin(17, 6);
    ledcAttachPin(5, 7);

    ledcSetup(0, PWM_Freq, PWM_Res);
    ledcSetup(1, PWM_Freq, PWM_Res);
    ledcSetup(2, PWM_Freq, PWM_Res);
    ledcSetup(3, PWM_Freq, PWM_Res);
    ledcSetup(4, PWM_Freq, PWM_Res);
    ledcSetup(5, PWM_Freq, PWM_Res);
    ledcSetup(6, PWM_Freq, PWM_Res);
    ledcSetup(7, PWM_Freq, PWM_Res);

    Serial.begin (115200);
    delay (2000);
    Serial << endl << endl << "Hello, I am an RTOS demonstration" << endl;

    // xTaskCreate (wifiTask,
    //             "WIFI",
    //             8192,
    //             NULL,
    //             1,
    //             NULL);

    xTaskCreate (task_controller,
                 "Controller",                    // Task name for printouts
                 8192,                            // Stack size
                 NULL,                            // Parameters for task fn.
                 2,                               // Priority
                 NULL);                           // Task handle


    xTaskCreate (task_encoder,
                 "ENC",                           // Task name for printouts
                 8192,                            // Stack size
                 NULL,                            // Parameters for task fn.
                 2,                               // Priority
                 NULL);                           // Task handle

    xTaskCreate (task_motor_0,
                 "Driver0",                         // Task name for printouts
                 4096,                              // Stack size
                 NULL,                              // Parameters for task fn.
                 3,                                 // Priority
                 NULL);                             // Task handle

    // Create a task which manages motor 1
    
    xTaskCreate (task_motor_1,
                 "Driver1",                         // Task name for printouts
                 4096,                              // Stack size
                 NULL,                              // Parameters for task fn.
                 3,                                 // Priority
                 NULL);                             // Task handle            
    
    // Create a task which manages motor 2
    
    xTaskCreate (task_motor_2,
                 "Driver1",                         // Task name for printouts
                 4096,                              // Stack size
                 NULL,                              // Parameters for task fn.
                 3,                                 // Priority
                 NULL);                             // Task handle            
    
    // Create a task which manages motor 3
    
    xTaskCreate (task_motor_3,
                 "Driver1",                         // Task name for printouts
                 4096,                              // Stack size
                 NULL,                              // Parameters for task fn.
                 3,                                 // Priority
                 NULL);                             // Task handle
}

void loop() {
  // put your main code here, to run repeatedly:
}