#include "QuadCopterConfig.h"

void LED_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct = {
		/* LED_R PC13 */  /* LED_G PC14 */  /* LED_B PC15 */
		.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_15,
		.GPIO_Mode = GPIO_Mode_OUT,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_PuPd = GPIO_PuPd_NOPULL
	};
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	SetLED(LED_G, ENABLE);
	SetLED(LED_R, ENABLE);
	SetLED(LED_B, ENABLE);
}

void SetLED(int LED, int state)
{
	PCO(LED) = state;
}

void LED_Toggle(int LED)
{
	PCO(LED) = ~PCO(LED);
}
