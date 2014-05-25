/*=====================================================================================================*/
/*=====================================================================================================*/
#include "QuadCopterConfig.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
Quaternion NumQ = {1, 0, 0, 0};
EulerAngle AngE = {0};
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Quaternion_ToNumQ
**功能 : 尤拉角轉四元數
**輸入 : *pNumQ, *pAngE
**輸出 : None
**使用 : Quaternion_ToNumQ(&NumQ, &AngE);
**=====================================================================================================*/
/*=====================================================================================================*/
void Quaternion_ToNumQ(Quaternion *pNumQ, EulerAngle *pAngE)
{
	float halfP = pAngE->Pitch / 2.0f;
	float halfR = pAngE->Roll / 2.0f;
	float halfY = pAngE->Yaw / 2.0f;

	float sinP = arm_sin_f32(halfP);
	float cosP = arm_cos_f32(halfP);
	float sinR = arm_sin_f32(halfR);
	float cosR = arm_cos_f32(halfR);
	float sinY = arm_sin_f32(halfY);
	float cosY = arm_cos_f32(halfY);

	pNumQ->q0 = cosY * cosR * cosP + sinY * sinR * sinP;
	pNumQ->q1 = cosY * cosR * sinP - sinY * sinR * cosP;
	pNumQ->q2 = cosY * sinR * cosP + sinY * cosR * sinP;
	pNumQ->q3 = sinY * cosR * cosP - cosY * sinR * sinP;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Quaternion_ToAngE
**功能 : 四元數轉尤拉角
**輸入 : *pNumQ, *pAngE
**輸出 : None
**使用 : Quaternion_ToAngE(&NumQ, &AngE);
**=====================================================================================================*/
/*=====================================================================================================*/
void Quaternion_ToAngE(Quaternion *pNumQ, EulerAngle *pAngE)
{
	float NumQ_T11 = pNumQ->q0 * pNumQ->q0 + pNumQ->q1 * pNumQ->q1 - pNumQ->q2 * pNumQ->q2 - pNumQ->q3 * pNumQ->q3;
	float NumQ_T12 = 2.0f * (pNumQ->q0 * pNumQ->q3 + pNumQ->q1 * pNumQ->q2);
	float NumQ_T13 = 2.0f * (pNumQ->q1 * pNumQ->q3 - pNumQ->q0 * pNumQ->q2);
	float NumQ_T23 = 2.0f * (pNumQ->q0 * pNumQ->q1 + pNumQ->q2 * pNumQ->q3);
	float NumQ_T33 = pNumQ->q0 * pNumQ->q0 - pNumQ->q1 * pNumQ->q1 - pNumQ->q2 * pNumQ->q2 + pNumQ->q3 * pNumQ->q3;

	pAngE->Pitch = -asinf(NumQ_T13);
	pAngE->Roll  = atan2f(NumQ_T23, NumQ_T33);
	pAngE->Yaw   = atan2f(NumQ_T12, NumQ_T11);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Quaternion_Multiply
**功能 : 四元數乘法
**輸入 : NowQ, OldQ
**輸出 : NewQ
**使用 : NewQ = Quaternion_Multiply(NowQ, OldQ);
**=====================================================================================================*/
/*=====================================================================================================*/
Quaternion Quaternion_Multiply(Quaternion NowQ, Quaternion OldQ)
{
	Quaternion NewQ;

	NewQ.q0 = NowQ.q0 * OldQ.q0 - NowQ.q1 * OldQ.q1 - NowQ.q2 * OldQ.q2 - NowQ.q3 * OldQ.q3;
	NewQ.q1 = NowQ.q0 * OldQ.q1 + NowQ.q1 * OldQ.q0 + NowQ.q2 * OldQ.q3 - NowQ.q3 * OldQ.q2;
	NewQ.q2 = NowQ.q0 * OldQ.q2 - NowQ.q1 * OldQ.q3 + NowQ.q2 * OldQ.q0 + NowQ.q3 * OldQ.q1;
	NewQ.q3 = NowQ.q0 * OldQ.q3 + NowQ.q1 * OldQ.q2 - NowQ.q2 * OldQ.q1 + NowQ.q3 * OldQ.q0;

	Quaternion_Normalize(&NewQ);

	return NewQ;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Quaternion_Normalize
**功能 : 四元數歸一化
**輸入 : *pNumQ
**輸出 : None
**使用 : Quaternion_Normalize(&NewQ);
**=====================================================================================================*/
/*=====================================================================================================*/
void Quaternion_Normalize(Quaternion *pNumQ)
{
	float Normalize = 0.0f;

	Normalize = invSqrtf(squa(pNumQ->q0) + squa(pNumQ->q1) + squa(pNumQ->q2) + squa(pNumQ->q3));

	pNumQ->q0 = pNumQ->q0 * Normalize;
	pNumQ->q1 = pNumQ->q1 * Normalize;
	pNumQ->q2 = pNumQ->q2 * Normalize;
	pNumQ->q3 = pNumQ->q3 * Normalize;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Quaternion_RungeKutta
**功能 : 一階龍格-庫塔法, 更新四元數
**輸入 : *pNumQ, GyrX, GyrY, GyrZ, helfTimes
**輸出 : None
**使用 : Quaternion_RungeKutta(&NumQ, GyrX, GyrY, GyrZ, helfT);
**=====================================================================================================*/
/*=====================================================================================================*/
void Quaternion_RungeKutta(Quaternion *pNumQ, float GyrX, float GyrY, float GyrZ, float helfTimes)
{
	pNumQ->q0 = pNumQ->q0 + (-pNumQ->q1 * GyrX - pNumQ->q2 * GyrY - pNumQ->q3 * GyrZ) * helfTimes;
	pNumQ->q1 = pNumQ->q1 + (pNumQ->q0 * GyrX - pNumQ->q3 * GyrY + pNumQ->q2 * GyrZ) * helfTimes;
	pNumQ->q2 = pNumQ->q2 + (pNumQ->q3 * GyrX + pNumQ->q0 * GyrY - pNumQ->q1 * GyrZ) * helfTimes;
	pNumQ->q3 = pNumQ->q3 + (-pNumQ->q2 * GyrX + pNumQ->q1 * GyrY + pNumQ->q0 * GyrZ) * helfTimes;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
