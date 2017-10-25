#include "MQ6812.h"
#include "iApp.h"
#include "FlashFunction.h"
#include "protocol.h"
#include "led.h"
#include "battery_detect.h"
#include "ADC.h"

extern uchar bat_qua;
extern char led_blink_f ;
void Display_LED_Discharge(void)
{
	ADC_BAT_check();
	switch(bat_qua)
	{
		case 0: {D1 = 0; D2 = 0; D3 = 0; D4 = 0; }	break;
		case 1: {D1 = 1; D2 = 0; D3 = 0; D4 = 0; }	break;
		case 2: {D1 = 1; D2 = 1; D3 = 0; D4 = 0; }	break;
		case 3: {D1 = 1; D2 = 1; D3 = 1; D4 = 0; }	break;
		case 4: {D1 = 1; D2 = 1; D3 = 1; D4 = 1; }	break;
		default :                                          	break;
	}
}
void Display_LED_Charge(void)
{
	ADC_BAT_check();
	switch(bat_qua)
	{
		case 0: LED_Blink1();    break;
		case 1: LED_Blink1();    break;
		case 2: LED_Blink2();    break;
		case 3: LED_Blink3();    break;
		case 4: LED_Blink4();    break;
		default :                                          break;
	}
}


void LED_Blink1(void)
{
	D1 = 1;
	if(led_blink_f)
	{
		D2 = 1;
		led_blink_f=0;
	}
	else
	{
		D2 = 0;
		led_blink_f=1;
	}
}
void LED_Blink2(void)
{
	D1 = 1;
	D2 = 1;
	if(led_blink_f)
	{
		D3 = 1;
		led_blink_f=0;
	}
	else
	{
		D3 = 0;
		led_blink_f=1;
	}
}
void LED_Blink3(void)
{
	D1 = 1;
	D2 = 1;
	D3 = 1;
	if(led_blink_f)
	{
		D4= 1;
		led_blink_f=0;
	}
	else
	{
		D4 = 0;
		led_blink_f=1;
	}
}
void LED_Blink4(void)
{
	D1 = 1;
	D2 = 1;
	D3 = 1;
	D4 = 1;

}