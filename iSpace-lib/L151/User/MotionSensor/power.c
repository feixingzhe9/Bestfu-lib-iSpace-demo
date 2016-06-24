#include "power.h"
void POWER_PIN_INIT(void)
{
	RF_POWER_OUT;
	LED_POWER_OUT;
//	VOICE_POWER_OUT;
//	TFT_POWER_OUT;
}
void POWER_ON(void)
{
	RF_POWER(1);
	LED_POWER(1);
//	VOICE_POWER(1);
//	TFT_POWER(1);
}
void POWER_OFF(void)
{
	RF_POWER(0);
	LED_POWER(0);
//	VOICE_POWER(0);
//	TFT_POWER(0);
}








