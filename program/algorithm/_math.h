#ifndef ___MATH_H
#define ___MATH_H

#include "arm_math.h"
#include "stm32f4xx.h"

#define invSqrtf(iSq) (1.0f/sqrtf((float)iSq))
#define squa(Sq)      (((float)Sq)*((float)Sq))
#define toRad(Math_D) ((float)(Math_D)*0.0174532925f)
#define toDeg(Math_R) ((float)(Math_R)*57.2957795f)

#endif
