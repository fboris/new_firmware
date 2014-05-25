#ifndef __STM32F4_DELAY_H
#define __STM32F4_DELAY_H

#include "stm32f4xx.h"

void Delay_nop(vu32);
void Delay_1us(vu32);
void Delay_10us(vu32);
void Delay_100us(vu32);
void Delay_1ms(vu32);
void Delay_10ms(vu32);
void Delay_100ms(vu32);

#endif
