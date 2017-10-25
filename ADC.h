
#ifndef __ADC_H_
#define __ADC_H_

/*********************************************
******	ADC Vref 2V ������ʹ��ע������	******
**********************************************
ADC(internal Vref 2V)����ʹ�÷�����ע������
ADC�ж���ģʽ������ģʽ(single mode)���ظ�ģʽ(repeat mode)��

1. ADC��ʼ��
	1-1. ��ȡADC �ڲ�Vref_2V֮ʵ��ֵ(��λΪmV), ��ȡֵΪ ( �ڲ�Vref 2V֮ʵ��ֵ * 1024 ),
	1-2. ����ADC�Զ�����:(MULCTR)(0x0EF6)=0x02
	1-3. ��ADCת��(������˵��), ȡ��ADC ƫ����(����ADC_offset)
2. ADCת��
	2-1. ��n��(����ADC_count)ת��, ȡ��n��ADC���֮�ܺ�(����ADC_sum), (n����ֵΪ32),
	2-3. (ADC_result)=(����ADC_sum)-(ADCƫ����), ���(ADC_result)С��(ADCƫ����), ��ȡ(ADC_result)Ϊ0
	2-2. ����ADC��ȷ���Ϊ:
			(ADC_result) / (ADCת������=n)
	2-4. �뽫���б���ת��Ϊunsigned long ��̬�Լ�����������ճ̵����

ע������:
	��ȡADC���ʱ���ȶ�ȡ��λ(ADCDRL)�ٶ�ȡ��λ(ADCDRH)
***********************************************/



/******************
 * 1st Argument
 * ****************/
#define		ADC_Single		0x1	// ����ת��ģʽ
#define		ADC_Repeat		0x3	// ����ת��ģʽ
/******************
 * 2nd Argument
 * ****************/
#define		AIN_DIS			0x0	// ��ֹģ���ź�����
#define		AIN_EN			0x1	// ����ģ���ź�����
/******************
 * 3rd Argument
 * ****************/
#define		AIN0			0x0	// ѡ���ⲿ��ѹ�����AIN0
#define		AIN1			0x1	// ѡ���ⲿ��ѹ�����AIN1
#define		AIN2			0x2	// ѡ���ⲿ��ѹ�����AIN2
#define		AIN3			0x3	// ѡ���ⲿ��ѹ�����AIN3
#define		AIN4			0x4	// ѡ���ⲿ��ѹ�����AIN4
#define		AIN5			0x5	// ѡ���ⲿ��ѹ�����AIN5
#define		AIN6			0x6	// ѡ���ⲿ��ѹ�����AIN6
#define		AIN7			0x7	// ѡ���ⲿ��ѹ�����AIN7
#define 	AIN8			0x8	// ѡ���ⲿ��ѹ�����AIN8
#define		VDD4_1			0x9	// ѡ���ڲ���ѹ���� (4��֮1 VDD)
#define		AIN_GND      	0xc	// �ڲ��ӵ�
/******************
 * 4th Argument
 * ****************/
// fcgck=16M... Conv256CLK(16us) ~ Conv1024CLK( 64us)
// fcgck= 8M... Conv128CLK(16us) ~ Conv1024CLK(128us)
// fcgck= 4M... Conv64CLK (16us) ~ Conv512CLK (128us)
// fcgck= 2M... Conv32CLK (16us) ~ Conv256CLK (128us)
#define		Conv32CLK		0x0	// ADת��ʱ��-  32������ʱ��
#define		Conv64CLK		0x1	// ADת��ʱ��-  64������ʱ��
#define		Conv128CLK		0x2	// ADת��ʱ��- 128������ʱ��
#define		Conv256CLK		0x3	// ADת��ʱ��- 256������ʱ��
#define		Conv512CLK		0x4	// ADת��ʱ��- 512������ʱ��
#define		Conv1024CLK		0x5	// ADת��ʱ��-1024������ʱ��
								// (*ע��ת��ʱ��Ӧ�趨��12.8 us ~ 128 us ��Χ��)
/******************
 * 5th Argument
 * ****************/
#define		Vref2			0x0	// ѡ���ڲ� 2V�ο���ѹ
#define		Vref3			0x1	// ѡ���ڲ� 3V�ο���ѹ
#define		Vref4			0x2	// ѡ���ڲ� 4V�ο���ѹ
#define		VDDVref			0x3	// ѡ���ڲ�VDD�ο���ѹ
#define		EXTVref			0x4	// ѡ���ⲿExt�ο���ѹ����ʹ����AIN3��ͬ�ĵ�28��(P43)��Ϊ
								// �ⲿ�ο���ѹ���룬�������ⲿ�ο���ѹʱ������ʹ��AIN3��Ϊ�ⲿ��ѹ����


//-- ����ȫ�ֱ��� --//
extern uint  ADC_Code_READ;
extern ulong ADC_VOLTAGE;
extern uchar data2Port[2];

extern uint  vref_l, vref_h;
extern ulong iReal_Vref2V, adc_value, adc_GND;


uint  GetVref(void);
ulong ADC_detect(uchar, uchar, uchar, uchar);
ulong ADC_ConvCode(uchar, uchar, uchar, uchar);
ulong ADC_ConvVolt(uchar, uchar, uchar, uchar);
uint  ADC_BAT_check(void);

#define	ad_test_times	8

#endif


















