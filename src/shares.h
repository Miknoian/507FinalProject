#ifndef _SHARES_H_
#define _SHARES_H_

#include "taskqueue.h"
#include "taskshare.h"

// A share which holds a counter of how many times a simulated event occurred
extern Share<int32_t> enc1_RPS;
extern Share<int32_t> enc2_RPS;
extern Share<int32_t> enc3_RPS;
extern Share<int32_t> enc4_RPS;
// extern Share<uint32_t> signal;
extern Share<uint32_t> stickAngle;
extern Share<uint32_t> stickMag;
extern Share<uint32_t> FL_pwm;
extern Share<uint32_t> FR_pwm;

#endif // _SHARES_H_
