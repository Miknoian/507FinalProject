/** @file shares.h
 * @brief Header file for shared variables
 * @details Sets up several variables as shared variables to be accessed by other tasks. Defines them as 'externs'
 * meaning they are defined elsewhere
 * @author Mark Iknoian
 * @date 05-Dec-2021
*/

#ifndef _SHARES_H_
#define _SHARES_H_

#include "taskqueue.h"
#include "taskshare.h"

// Encoder Shares
extern Share<float> enc0_RPS;       // Share for encoder 0 velocity in rad/s
extern Share<float> enc1_RPS;       // Share for encoder 1 velocity in rad/s
extern Share<float> enc2_RPS;       // Share for encoder 2 velocity in rad/s
extern Share<float> enc3_RPS;       // Share for encoder 3 velocity in rad/s

// WiFi Shares
extern Share<uint32_t> stickAngle;  // Share for stick angle in degrees
extern Share<uint32_t> stickMag;    // Share for stick velocity in percent

extern Share<bool> FL_dir;          // Share for front left wheel direction
extern Share<bool> BL_dir;          // Share for back left wheel direction
extern Share<bool> FR_dir;          // Share for front right wheel direction
extern Share<bool> BR_dir;          // Share for back right wheel direction

extern Share<uint32_t> FL_pwm;      // Share for front left wheel PWM
extern Share<uint32_t> BL_pwm;      // Share for back left wheel PWM
extern Share<uint32_t> FR_pwm;      // Share for front right wheel PWM
extern Share<uint32_t> BR_pwm;      // Share for back right wheel PWM


#endif // _SHARES_H_
