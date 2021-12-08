/** @file task_encoder.h
 * @brief Header file for task_encoder.cpp
* @author Mark Iknoian
* @date 12/7/2021
*/

#ifndef _TASK_ENCODER_H_
#define _TASK_ENCODER_H_

#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Encoder.h>

/// @brief Function to run encoders
void task_encoder (void* p_params);

#endif