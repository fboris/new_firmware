#include "stm32f4xx.h"

#ifndef __QUATERNION_H
#define __QUATERNION_H

typedef struct {
	float Pitch;
	float Roll;
	float Yaw;
} EulerAngle;

typedef struct {
	float q0;
	float q1;
	float q2;
	float q3;
} Quaternion;

void Quaternion_ToNumQ(Quaternion *, EulerAngle *);
void Quaternion_ToAngE(Quaternion *, EulerAngle *);
Quaternion Quaternion_Multiply(Quaternion, Quaternion);
void Quaternion_Normalize(Quaternion *);
void Quaternion_RungeKutta(Quaternion *, float, float, float, float);

extern Quaternion NumQ;
extern EulerAngle AngE;

#endif
