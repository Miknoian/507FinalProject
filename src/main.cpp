/** @file main.cpp
 * @brief Main function to run all tasks
 * @details Sets up shared variables, sets up pinmode for PWM and then runs tasks based on priorites and run time
 * @author Mark Iknoian, Daniel Freeman, Joshua Hoye
 * @date 05-Dec-2021
*/
#include <Arduino.h>
#include <PrintStream.h>
#include "task_encoder.h"
#include "task_controller.h"
#include "taskqueue.h"
#include "taskshare.h"
#include "shares.h"
#include "wifiTask.h"
#include "task_motor.h"           // Header for motor driver module

Share<int32_t> enc1_RPS ("sneed1");     /// Share for encoder 1 data in rad/s
Share<int32_t> enc2_RPS ("sneed2");     /// Share for encoder 2 data in rad/s
Share<int32_t> enc3_RPS ("sneed3");     /// Share for encoder 3 data in rad/s
Share<int32_t> enc4_RPS ("sneed4");     /// Share for encoder 4 data in rad/s
Share<uint32_t> stickAngle  ("sneed6"); /// Share for joystick angle in degrees
Share<uint32_t> stickMag  ("sneed7");   /// Share for joystick velocity

void setup() 
{
    //The following pins are used to control the motors. They must be set here because they cause a reboot loop when in a task.
    const uint16_t PWM_Freq = 1000;
    const uint8_t PWM_Res = 8;

    ledcAttachPin(33, 0);
    ledcAttachPin(25, 1);
    
    ledcAttachPin(14, 2);
    ledcAttachPin(27, 3);
    
    ledcAttachPin(18, 5);
    ledcAttachPin(19, 4);

    ledcAttachPin(17, 7);
    ledcAttachPin(5, 6);

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

    xTaskCreate (wifiTask,
                "WIFI",
                8192,
                NULL,
                1,
                NULL);

    xTaskCreate (task_controller,
            "Controller",
            16384,
            NULL,
            1,
            NULL);

    // xTaskCreate (task_encoder,
    //              "ENC",                           // Task name for printouts
    //              16384,                            // Stack size
    //              NULL,                            // Parameters for task fn.
    //              2,                               // Priority
    //              NULL);                           // Task handle

     xTaskCreate (task_motor_0,
                  "Driver0",                         // Task name for printouts
                  4096,                              // Stack size
                  NULL,                              // Parameters for task fn.
                  3,                                 // Priority
                  NULL);                             // Task handle

    // // // Create a task which manages motor 1
    
     xTaskCreate (task_motor_1,
                  "Driver1",                         // Task name for printouts
                  4096,                              // Stack size
                  NULL,                              // Parameters for task fn.
                  3,                                 // Priority
                  NULL);                             // Task handle            
    
    // // // Create a task which manages motor 2
    
     xTaskCreate (task_motor_2,
                  "Driver1",                         // Task name for printouts
                  4096,                              // Stack size
                  NULL,                              // Parameters for task fn.
                  3,                                 // Priority
                  NULL);                             // Task handle            
    
    // // // Create a task which manages motor 3
    
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