/** @file task_encoder.h
 * @brief Header for encoder task 
 * @author Mark Iknoian
 * @date 05-Dec-2021
*/
#ifndef _TASK_ENCODER_H_
#define _TASK_ENCODER_H_

#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Encoder.h>

///@brief Function for encoders
void task_encoder (void* p_params);

#endif