//******************************************
//           This is a C Template file
//作者
//日期
//功能
//备注
//******************************************
#include "MQ6812.h"
#include "iApp.h"
#include "ADC.h"



uint  ADC_Code_READ;
ulong ADC_VOLTAGE;
uchar data2Port[2];

uint  vref_l, vref_h;
ulong iReal_Vref2V, adc_value, adc_GND;

extern uchar bat_qua;

//*********************************************************************
// 函数名	: GetVref()
// 函数功能	: 读取ADC 内部Vref 2V之实际值(单位为mV), 存入变数 (ADC_vref2v)
// 			: 读取值为 ( 内部Vref 2V之实际值 * 1024 ), 单位为mV
// 备注		: 启动ADC自动补偿:(MULCTR)(0x0EF6)=0x02
//*********************************************************************
uint GetVref(void)
{
	TYPE_WORD ADC_READ;
//	Vref2V, value is ( Real_2V * 1024 )
	__asm("LD A,(0x7E05)");		// low byte
	__asm("LD (_vref_l),A");
	__asm("LD A,(0x7E06)");		// high byte
	__asm("LD (_vref_h),A");

	ADC_READ.byte[0] = vref_l;
	ADC_READ.byte[1] = vref_h & 0x0f;

	MULCTR.byte = 0x02;			// 启动ADC自动补偿:(MULCTR)(0ex0EF6)=0x02
	if( ADC_READ.word > 2150 )	MULCTR.byte = 0x00;	// 如果 Vref2V超出范围, 则不启动ADC自动补偿
	if( ADC_READ.word < 1950 )	MULCTR.byte = 0x00;	// 如果 Vref2V超出范围, 则不启动ADC自动补偿
	return ADC_READ.word;
}
//uint GetVref(void)
//{
////	__asm("LD A,(0x7E05)");		// low byte
////	__asm("LD A,(0x7E06)");		// high byte
//	uint *adc_value = (uint*)(0x7E05);
//	uint adc_read;

//	adc_read = *adc_value & 0x0fff;
//	MULCTR.byte = 0x02;			// 启动ADC自动补偿:(MULCTR)(0ex0EF6)=0x02
//	if( adc_read > 2150 )	MULCTR.byte = 0x00;	// 如果 Vref2V超出范围, 则不启动ADC自动补偿
//	if( adc_read < 1950 )	MULCTR.byte = 0x00; // 如果 Vref2V超出范围, 则不启动ADC自动补偿
//	return adc_read;
//}


//*********************************************************************
// 函数名	: ADC_detect()
// 函数功能	: 作32次(变量ADC_count)转换, 取得32次ADC结果之总和(变量ADC_sum)
// 备注		: 建议取32次平均 (由 ad_test_times = 32 设定)
//*********************************************************************
ulong ADC_detect(uchar VREF, uchar SAIN, uchar ACK, uchar AMD)
{
	char  i;
	ulong adc_data = 0;
	TYPE_WORD ADC_READ;

//	ADC Config set ......
	ADCVRF.byte  = VREF;
	ADCCR1.byte  = SAIN;	// 1. 设定SAIN，选择进行AD 转换的模拟信号输入通道
	ADCCR1.byte |= 16;		// 2. 设定模拟信号输入控制AINEN 为"允许模拟信号输入"
	ADCCR1.byte |= AMD*32;	// 3. 设定AMD，选择AD 转换模式为单次或重复模式
	ADCCR2.byte  = ACK;

//	ADC Single mode ......
	if( AMD == ADC_Single )
	{
		for( i=0; i<ad_test_times; i++ )
		{
			ADCCR1.bit.b7 = 1;			// start adc检测
			while(  ADCCR2.bit.b6 ){}	// 等待adc开始转换
			while( !ADCCR2.bit.b7 ){}	// 等待adc转换结束
			ADC_READ.byte[0] = ADCDRL.byte;
			ADC_READ.byte[1] = ADCDRH.byte;
			adc_data += ADC_READ.word;
		}
	}
//	ADC Repeat mode ......
	else
	{
		ADCCR1.bit.b7 = 1;				// start adc检测
		for( i=0; i<ad_test_times; i++ )
		{
			while( !ADCCR2.bit.b7 ){}	// 等待adc转换结束
			ADC_READ.byte[0] = ADCDRL.byte;
			ADC_READ.byte[1] = ADCDRH.byte;
			adc_data += ADC_READ.word;
		}
		ADCCR1.byte = 0x00;				// stop adc检测
	}

	return adc_data;
}


//*********************************************************************
// 函数名	: ADC_ConvCode()
// 函数功能	:
// 备注		: AD转换结果为 AIN 之 ADC Code
// 			: fcgck=16M... Conv256CLK(16us) ~ Conv1024CLK( 64us)
// 			: fcgck= 8M... Conv128CLK(16us) ~ Conv1024CLK(128us)
// 			: fcgck= 4M... Conv64CLK (16us) ~ Conv512CLK (128us)
// 			: fcgck= 2M... Conv32CLK (16us) ~ Conv256CLK (128us)
//*********************************************************************
ulong ADC_ConvCode(uchar VREF, uchar SAIN, uchar ACK, uchar AMD)
{
	adc_value = ADC_detect(VREF,    SAIN, ACK, AMD);
	adc_value = adc_value / ad_test_times;

	return adc_value;
}

//*********************************************************************
// 函数名	: ADC_ConvVolt()
// 函数功能	:
// 备注		: AD转换结果为 AIN 之 电压值(mV)
// 			: fcgck=16M... Conv256CLK(16us) ~ Conv1024CLK( 64us)
// 			: fcgck= 8M... Conv128CLK(16us) ~ Conv1024CLK(128us)
// 			: fcgck= 4M... Conv64CLK (16us) ~ Conv512CLK (128us)
// 			: fcgck= 2M... Conv32CLK (16us) ~ Conv256CLK (128us)
//*********************************************************************
ulong ADC_ConvVolt(uchar VREF, uchar SAIN, uchar ACK, uchar AMD)
{
	if( VREF == Vref2 )
	{
		adc_value = ADC_detect(VREF,    SAIN, ACK, AMD);

//P8DR.bit.b1 = 1;	// 观察执行时间，可以删除
	//	减去ADC偏移量, 先比较ADC结果, 如果ADC结果小于偏移量, 则取ADC结果为0
	//	转换为 ADC Voltage
		adc_value = (adc_value*2000) / 1024 / ad_test_times;
//P8DR.bit.b1 = 0;	// 观察执行时间，可以删除
		return adc_value;
	}

	return 9999;	// 只用于VREF2V, 否则传回固定值
}

//********> cADC_correct = ( iADC_value*iReal_Vref2V ) / 2000 / 32;
//ADC_correct_code(结果)_  = 平均值*实际参考电压/理想参考电压
// 可用于 adc_code的比较, 仅用于选择内部2V参考电压
//********> vADC_correct = cADC_correct * 2000 / 1023;
//ADC_correct_voltage(mV)_ = ADC_correct_code(结果)*理想参考电压/1023
// 可用于与目标电压值比较, 仅用于选择内部2V参考电压




//*********************************************************************
// 函数名	: ADC_ConvCode()
// 函数功能	:
// 备注		: AD转换结果为 AIN 之 ADC Code
// 			: fcgck=16M... Conv256CLK(16us) ~ Conv1024CLK( 64us)
// 			: fcgck= 8M... Conv128CLK(16us) ~ Conv1024CLK(128us)
// 			: fcgck= 4M... Conv64CLK (16us) ~ Conv512CLK (128us)
// 			: fcgck= 2M... Conv32CLK (16us) ~ Conv256CLK (128us)

//          : #define		Vref2			0x0	// 选择内部 2V参考电压
//          : #define		VDDVref			0x3	// 选择内部VDD参考电压

//*********************************************************************
uint ADC_BAT_check(void)
{

	adc_value = ADC_detect( Vref2, AIN6, Conv512CLK, ADC_Single );
	adc_value = adc_value / ad_test_times;

    if( adc_value >= 1000 )
    {
         D1 = 1;
         D2 = 1;
         D3 = 1;
         D4 = 1;
		 //bat_qua = 4;
    }
    else if( adc_value >= 997 )
    {
         D1 = 1;
         D2 = 1;
         D3 = 1;
         D4 = 0;
		 //bat_qua = 3;
    }
    else if( adc_value >= 985 )
    {
         D1 = 1;
         D2 = 1;
         D3 = 0;
         D4 = 0;
		 //bat_qua = 2;
    }
    else if( adc_value >= 972 )
    {
         D1 = 1;
         D2 = 0;
         D3 = 0;
         D4 = 0;
		 //bat_qua = 1;
    }
    else
    {
         D1 = 0;
         D2 = 0;
         D3 = 0;
         D4 = 0;
		// bat_qua = 0;
    }

	return adc_value;
}

uchar  ADC_VBUS_check(void)
{

	adc_value = ADC_detect( Vref2, AIN5, Conv512CLK, ADC_Single );
	adc_value = adc_value / ad_test_times;

    if( adc_value >= 1000 )

	return adc_value;
}








