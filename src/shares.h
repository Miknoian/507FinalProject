#ifndef _SHARES_H_
#define _SHARES_H_

#include "taskqueue.h"
#include "taskshare.h"

// A share which holds a counter of how many times a simulated event occurred
extern Share<float> enc0_RPS;
extern Share<float> enc1_RPS;
extern Share<float> enc2_RPS;
extern Share<float> enc3_RPS;

// extern Share<uint32_t> signal;
extern Share<uint32_t> stickAngle;
extern Share<uint32_t> stickMag;

extern Share<bool> FL_dir; // 1 = forward, 0 = backward
extern Share<bool> BL_dir;
extern Share<bool> FR_dir;
extern Share<bool> BR_dir;

extern Share<uint32_t> FL_pwm;
extern Share<uint32_t> BL_pwm;
extern Share<uint32_t> FR_pwm;
extern Share<uint32_t> BR_pwm;


#endif // _SHARES_H_
