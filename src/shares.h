#ifndef _SHARES_H_
#define _SHARES_H_

#include "taskqueue.h"
#include "taskshare.h"

// A share which holds a counter of how many times a simulated event occurred
extern Share<int32_t> enc1_RPS;
extern Share<int32_t> enc2_RPS;
extern Share<int32_t> enc3_RPS;
extern Share<int32_t> enc4_RPS;

#endif // _SHARES_H_