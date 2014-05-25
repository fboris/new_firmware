#include "QuadCopterConfig.h"
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MoveAve_SMA
**功能 : Simple Moving Average
**輸入 : NewData, MoveAve_FIFO, SampleNum
**輸出 : AveData
**使用 : MoveAve_SMA(NewData, MoveAve_FIFO, SampleNum)
**=====================================================================================================*/
/*=====================================================================================================*/
s16 MoveAve_SMA(volatile int16_t NewData, volatile int16_t *MoveAve_FIFO, u8 SampleNum)
{
	u8 i = 0;
	s16 AveData = 0;
	s32 MoveAve_Sum = 0;

	for (i = 0; i < SampleNum - 1; i++)       // 陣列移動
		MoveAve_FIFO[i] = MoveAve_FIFO[i + 1];

	MoveAve_FIFO[SampleNum - 1] = NewData;    // 加入新數據

	for (i = 0; i < SampleNum; i++)           // 求和
		MoveAve_Sum += MoveAve_FIFO[i];

	AveData = (s16)(MoveAve_Sum / SampleNum); // 計算平均值

	return AveData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MoveAve_WMA
**功能 : Weighted Moving Average
**輸入 : NewData, MoveAve_FIFO, SampleNum
**輸出 : AveData
**使用 : MoveAve_WMA(NewData, MoveAve_FIFO, SampleNum)
**=====================================================================================================*/
/*=====================================================================================================*/
s16 MoveAve_WMA(volatile int16_t NewData, volatile int16_t *MoveAve_FIFO, u8 SampleNum)
{
	u8 i = 0;
	s16 AveData = 0;
	u16 SampleSum = 0;
	s32 MoveAve_Sum = 0;

	for (i = 0; i < SampleNum - 1; i++)         // 陣列移動
		MoveAve_FIFO[i] = MoveAve_FIFO[i + 1];

	MoveAve_FIFO[SampleNum - 1] = NewData;      // 加入新數據

	for (i = 0; i < SampleNum; i++)             // 求和 & 加權
		MoveAve_Sum += MoveAve_FIFO[i] * (i + 1);

	SampleSum = (SampleNum * (SampleNum + 1)) / 2; // 計算加權除數
	AveData = (s16)(MoveAve_Sum / SampleSum);   // 計算平均值

	return AveData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MoveAve_EMA
**功能 : Exponential Moving Average
**輸入 : NewData, MoveAve_FIFO, SampleNum
**輸出 : AveData
**使用 : MoveAve_EMA(NewData, MoveAve_FIFO, SampleNum)
*/
