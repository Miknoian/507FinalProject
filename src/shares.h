#ifndef _SHARES_H_
#define _SHARES_H_

#include "taskqueue.h"
#include "taskshare.h"

// A share which holds a counter of how many times a simulated event occurred
extern Share<int32_t> enc1_RPS;
extern Share<int32_t> enc2_RPS;
extern Share<int32_t> enc3_RPS;
extern Share<int32_t> enc4_RPS;

extern Share<uint32_t> signal;

extern Share<uint8_t> FL_mag;
extern Share<uint8_t> FR_mag;
extern Share<uint8_t> BL_mag;
extern Share<uint8_t> BR_mag;

extern Share<bool> FL_dir;
extern Share<bool> FR_dir;
extern Share<bool> BL_dir;
extern Share<bool> BR_dir;

#endif // _SHARES_H_
