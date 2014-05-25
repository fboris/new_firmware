#include "QuadCopterConfig.h"

PID_t PID_Yaw = {
	.Kp = 0.0f, .Ki  = 0.0f, .Kd = 0.0f,
	.Err0 = 0.0f, .Err1 = 0.0f, .Err2 = 0.0f,
	.SumErr = 0.0f, .ZeroErr = 0.0f,
	.KiMax = +400.0f, .KiMin = -400.0f,
	.OutMax = +800.0f, .OutMin = -800.0f,
	.Output = 0.0f
};

PID_t PID_Roll = {
	.Kp = 0.0f, .Ki  = 0.0f, .Kd = 0.0f,
	.Err0 = 0.0f, .Err1 = 0.0f, .Err2 = 0.0f,
	.SumErr = 0.0f, .ZeroErr = 0.0f,
	.KiMax = +400.0f, .KiMin = -400.0f,
	.OutMax = +800.0f, .OutMin = -800.0f,
	.Output = 0.0f
};

PID_t PID_Pitch = {
	.Kp = 0.0f, .Ki  = 0.0f, .Kd = 0.0f,
	.Err0 = 0.0f, .Err1 = 0.0f, .Err2 = 0.0f,
	.SumErr = 0.0f, .ZeroErr = 0.0f,
	.KiMax = +400.0f, .KiMin = -400.0f,
	.OutMax = +800.0f, .OutMin = -800.0f,
	.Output = 0.0f
};

/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : PID_Init
**功能 : PID Initialize
**輸入 : PID
**輸出 : None
**使用 : PID_Init(&PID);
**=====================================================================================================*/
/*=====================================================================================================*/
void PID_Init(PID_t *PID, float Kp, float Ki, float Kd)
{
	PID->Kp      = Kp;
	PID->Ki      = Ki;
	PID->Kd      = Kd;

	PID->Err0    = 0.0f;
	PID->Err1    = 0.0f;
	PID->Err2    = 0.0f;
	PID->SumErr  = 0.0f;
	PID->ZeroErr = 0.0f;
	PID->Output  = 0.0f;
	PID->KiMax   = +400.0f;
	PID->KiMin   = -400.0f;
	PID->OutMax  = +800.0f;
	PID->OutMin  = -800.0f;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : PID_IncCal
**功能 : Calculate Incremental PID
**輸入 : PID, CurrentVal
**輸出 : None
**使用 : PID_IncCal(&PID, CurrentVal)
**=====================================================================================================*/
/*=====================================================================================================*/
float PID_IncCal(PID_t *PID, float CurrentVal)
{
	float Value_Kp;	// 比例
	float Value_Ki;	// 積分
	float Value_Kd;	// 微分

	PID->Err0 = PID->Err1;
	PID->Err1 = PID->Err2;
	PID->Err2 = CurrentVal - PID->ZeroErr;

	Value_Kp    = PID->Kp * (PID->Err2 - PID->Err1);
	Value_Ki    = PID->Ki * PID->Err2;
	Value_Kd    = PID->Kd * (PID->Err2 - 2.0f * PID->Err1 + PID->Err0);
	PID->Output = Value_Kp + Value_Ki + Value_Kd;

	if (PID->Output > PID->OutMax)
		PID->Output = PID->OutMax;

	if (PID->Output < PID->OutMin)
		PID->Output = PID->OutMin;

	return (PID->Output);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : PID_IncCal
**功能 : Calculate Positional PID
**輸入 : PID, CurrentVal
**輸出 : None
**使用 : PID_PosCal(&PID, CurrentVal)
**=====================================================================================================*/
/*=====================================================================================================*/
float PID_PosCal(PID_t *PID, float CurrentVal)
{
	float Value_Kp;	// 比例
	float Value_Ki;	// 積分
	float Value_Kd;	// 微分

	PID->Err1 = PID->Err2;
	PID->Err2 = CurrentVal - PID->ZeroErr;

	PID->SumErr += PID->Err2;

	Value_Kp = PID->Kp * PID->Err2;
	Value_Ki = PID->Ki * PID->SumErr;
	Value_Kd = PID->Kd * (PID->Err2 - PID->Err1);

	if (Value_Ki > PID->KiMax) {
		PID->SumErr -= PID->Err2;
		Value_Ki = PID->KiMax;
	}

	if (Value_Ki < PID->KiMin) {
		PID->SumErr -= PID->Err2;
		Value_Ki = PID->KiMin;
	}

	PID->Output = Value_Kp + Value_Ki + Value_Kd;

	if (PID->Output > PID->OutMax)
		PID->Output = PID->OutMax;

	if (PID->Output < PID->OutMin)
		PID->Output = PID->OutMin;

	return (PID->Output);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : PID_AHRS_Cal
**功能 :
**輸入 : PID, Angle, Gyroscope
**輸出 : None
**使用 : PID_AHRS_Cal(&PID, Angle, Gyroscope);
**=====================================================================================================*/
/*=====================================================================================================*/
float PID_AHRS_Cal(PID_t *PID, float Angle, float Gyroscope)
{
	float Value_Kp;	// 比例
	float Value_Ki;	// 積分
	float Value_Kd;	// 微分

	PID->Err1 = PID->ZeroErr - Angle;

	PID->SumErr = PID->SumErr + PID->Err1;

	Value_Kp = PID->Kp * PID->Err1;
	Value_Ki = PID->Ki * PID->SumErr;
	Value_Kd = PID->Kd * Gyroscope;

	if (Value_Ki > PID->KiMax)
		Value_Ki = PID->KiMax;

	if (Value_Ki < PID->KiMin)
		Value_Ki = PID->KiMin;

	PID->Output = Value_Kp + Value_Ki - Value_Kd;

	if (PID->Output > PID->OutMax)
		PID->Output = PID->OutMax;

	if (PID->Output < PID->OutMin)
		PID->Output = PID->OutMin;

	return (-PID->Output);
}

float PID_AHRS_CalYaw(PID_t *PID, float Angle, float Gyroscope)
{
	float minErr = 0.0f;
	float Value_Kp;	// 比例
	float Value_Ki;	// 積分
	float Value_Kd;	// 微分

	PID->Err1 = PID->ZeroErr - Angle;

	minErr = fabsf(PID->Err1);

	if ((minErr > 180.0f) && (PID->Err1 < 0.0f))
		PID->Err1 = minErr - 360.0f;
	else if ((minErr > 180.0f) && (PID->Err1 > 0.0f))
		PID->Err1 = 360.0f - minErr;
	else if ((minErr < 180.0f) && (PID->Err1 < 0.0f))
		PID->Err1 = minErr;
	else
		PID->Err1 = 0.0f - minErr;

	PID->SumErr = PID->SumErr + PID->Err1;

	Value_Kp = PID->Kp * PID->Err1;
	Value_Ki = PID->Ki * PID->SumErr;
	Value_Kd = PID->Kd * Gyroscope;

	if (Value_Ki > PID->KiMax)
		Value_Ki = PID->KiMax;

	if (Value_Ki < PID->KiMin)
		Value_Ki = PID->KiMin;

	PID->Output = Value_Kp + Value_Ki - Value_Kd;

	if (PID->Output > PID->OutMax)
		PID->Output = PID->OutMax;

	if (PID->Output < PID->OutMin)
		PID->Output = PID->OutMin;

	return (-PID->Output);
}

