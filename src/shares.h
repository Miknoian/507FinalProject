/** @file shares.ch
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

extern Share<int32_t> enc1_RPS;     /// Share for encoder 1 data in rad/s
extern Share<int32_t> enc2_RPS;     /// Share for encoder 2 data in rad/s
extern Share<int32_t> enc3_RPS;     /// Share for encoder 3 data in rad/s
extern Share<int32_t> enc4_RPS;     /// Share for encoder 4 data in rad/s
extern Share<uint32_t> stickAngle;  /// Share for joystick angle in degrees
extern Share<uint32_t> stickMag;    /// Share for joystick velocity 

#endif // _SHARES_H_
