/** @file task_controller.h
 * @brief Header file for task_controller.cpp
* @author Joshua Hoye
*/

#ifndef _TASK_CONTROLLER_H_
#define _TASK_CONTROLLER_H_

#include <Arduino.h>
#include <PrintStream.h>
#include <ESP32Encoder.h>

/// @brief Function for control
void task_controller (void* p_params);

#endif