//******************************************
//           This is a C Template file
//����
//����
//����
//��ע
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
// ������	: GetVref()
// ��������	: ��ȡADC �ڲ�Vref 2V֮ʵ��ֵ(��λΪmV), ������� (ADC_vref2v)
// 			: ��ȡֵΪ ( �ڲ�Vref 2V֮ʵ��ֵ * 1024 ), ��λΪmV
// ��ע		: ����ADC�Զ�����:(MULCTR)(0x0EF6)=0x02
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

	MULCTR.byte = 0x02;			// ����ADC�Զ�����:(MULCTR)(0ex0EF6)=0x02
	if( ADC_READ.word > 2150 )	MULCTR.byte = 0x00;	// ��� Vref2V������Χ, ������ADC�Զ�����
	if( ADC_READ.word < 1950 )	MULCTR.byte = 0x00;	// ��� Vref2V������Χ, ������ADC�Զ�����
	return ADC_READ.word;
}
//uint GetVref(void)
//{
////	__asm("LD A,(0x7E05)");		// low byte
////	__asm("LD A,(0x7E06)");		// high byte
//	uint *adc_value = (uint*)(0x7E05);
//	uint adc_read;

//	adc_read = *adc_value & 0x0fff;
//	MULCTR.byte = 0x02;			// ����ADC�Զ�����:(MULCTR)(0ex0EF6)=0x02
//	if( adc_read > 2150 )	MULCTR.byte = 0x00;	// ��� Vref2V������Χ, ������ADC�Զ�����
//	if( adc_read < 1950 )	MULCTR.byte = 0x00; // ��� Vref2V������Χ, ������ADC�Զ�����
//	return adc_read;
//}


//*********************************************************************
// ������	: ADC_detect()
// ��������	: ��32��(����ADC_count)ת��, ȡ��32��ADC���֮�ܺ�(����ADC_sum)
// ��ע		: ����ȡ32��ƽ�� (�� ad_test_times = 32 �趨)
//*********************************************************************
ulong ADC_detect(uchar VREF, uchar SAIN, uchar ACK, uchar AMD)
{
	char  i;
	ulong adc_data = 0;
	TYPE_WORD ADC_READ;

//	ADC Config set ......
	ADCVRF.byte  = VREF;
	ADCCR1.byte  = SAIN;	// 1. �趨SAIN��ѡ�����AD ת����ģ���ź�����ͨ��
	ADCCR1.byte |= 16;		// 2. �趨ģ���ź��������AINEN Ϊ"����ģ���ź�����"
	ADCCR1.byte |= AMD*32;	// 3. �趨AMD��ѡ��AD ת��ģʽΪ���λ��ظ�ģʽ
	ADCCR2.byte  = ACK;

//	ADC Single mode ......
	if( AMD == ADC_Single )
	{
		for( i=0; i<ad_test_times; i++ )
		{
			ADCCR1.bit.b7 = 1;			// start adc���
			while(  ADCCR2.bit.b6 ){}	// �ȴ�adc��ʼת��
			while( !ADCCR2.bit.b7 ){}	// �ȴ�adcת������
			ADC_READ.byte[0] = ADCDRL.byte;
			ADC_READ.byte[1] = ADCDRH.byte;
			adc_data += ADC_READ.word;
		}
	}
//	ADC Repeat mode ......
	else
	{
		ADCCR1.bit.b7 = 1;				// start adc���
		for( i=0; i<ad_test_times; i++ )
		{
			while( !ADCCR2.bit.b7 ){}	// �ȴ�adcת������
			ADC_READ.byte[0] = ADCDRL.byte;
			ADC_READ.byte[1] = ADCDRH.byte;
			adc_data += ADC_READ.word;
		}
		ADCCR1.byte = 0x00;				// stop adc���
	}

	return adc_data;
}


//*********************************************************************
// ������	: ADC_ConvCode()
// ��������	:
// ��ע		: ADת�����Ϊ AIN ֮ ADC Code
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
// ������	: ADC_ConvVolt()
// ��������	:
// ��ע		: ADת�����Ϊ AIN ֮ ��ѹֵ(mV)
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

//P8DR.bit.b1 = 1;	// �۲�ִ��ʱ�䣬����ɾ��
	//	��ȥADCƫ����, �ȱȽ�ADC���, ���ADC���С��ƫ����, ��ȡADC���Ϊ0
	//	ת��Ϊ ADC Voltage
		adc_value = (adc_value*2000) / 1024 / ad_test_times;
//P8DR.bit.b1 = 0;	// �۲�ִ��ʱ�䣬����ɾ��
		return adc_value;
	}

	return 9999;	// ֻ����VREF2V, ���򴫻ع̶�ֵ
}

//********> cADC_correct = ( iADC_value*iReal_Vref2V ) / 2000 / 32;
//ADC_correct_code(���)_  = ƽ��ֵ*ʵ�ʲο���ѹ/����ο���ѹ
// ������ adc_code�ıȽ�, ������ѡ���ڲ�2V�ο���ѹ
//********> vADC_correct = cADC_correct * 2000 / 1023;
//ADC_correct_voltage(mV)_ = ADC_correct_code(���)*����ο���ѹ/1023
// ��������Ŀ���ѹֵ�Ƚ�, ������ѡ���ڲ�2V�ο���ѹ




//*********************************************************************
// ������	: ADC_ConvCode()
// ��������	:
// ��ע		: ADת�����Ϊ AIN ֮ ADC Code
// 			: fcgck=16M... Conv256CLK(16us) ~ Conv1024CLK( 64us)
// 			: fcgck= 8M... Conv128CLK(16us) ~ Conv1024CLK(128us)
// 			: fcgck= 4M... Conv64CLK (16us) ~ Conv512CLK (128us)
// 			: fcgck= 2M... Conv32CLK (16us) ~ Conv256CLK (128us)

//          : #define		Vref2			0x0	// ѡ���ڲ� 2V�ο���ѹ
//          : #define		VDDVref			0x3	// ѡ���ڲ�VDD�ο���ѹ

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








