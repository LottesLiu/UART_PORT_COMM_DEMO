
#ifndef __ADC_H_
#define __ADC_H_

/*********************************************
******	ADC Vref 2V 建议与使用注意事项	******
**********************************************
ADC(internal Vref 2V)建议使用方法与注意事项
ADC有二种模式：单次模式(single mode)与重复模式(repeat mode)。

1. ADC初始化
	1-1. 读取ADC 内部Vref_2V之实际值(单位为mV), 读取值为 ( 内部Vref 2V之实际值 * 1024 ),
	1-2. 启动ADC自动补偿:(MULCTR)(0x0EF6)=0x02
	1-3. 做ADC转换(见下面说明), 取得ADC 偏移量(变量ADC_offset)
2. ADC转换
	2-1. 作n次(变量ADC_count)转换, 取得n次ADC结果之总和(变量ADC_sum), (n建议值为32),
	2-3. (ADC_result)=(变量ADC_sum)-(ADC偏移量), 如果(ADC_result)小于(ADC偏移量), 则取(ADC_result)为0
	2-2. 计算ADC精确结果为:
			(ADC_result) / (ADC转换次数=n)
	2-4. 请将所有变量转换为unsigned long 型态以减少运算过程照程的误差

注意事项:
	读取ADC结果时请先读取低位(ADCDRL)再读取高位(ADCDRH)
***********************************************/



/******************
 * 1st Argument
 * ****************/
#define		ADC_Single		0x1	// 单次转换模式
#define		ADC_Repeat		0x3	// 连续转换模式
/******************
 * 2nd Argument
 * ****************/
#define		AIN_DIS			0x0	// 禁止模拟信号输入
#define		AIN_EN			0x1	// 允许模拟信号输入
/******************
 * 3rd Argument
 * ****************/
#define		AIN0			0x0	// 选择外部电压输入脚AIN0
#define		AIN1			0x1	// 选择外部电压输入脚AIN1
#define		AIN2			0x2	// 选择外部电压输入脚AIN2
#define		AIN3			0x3	// 选择外部电压输入脚AIN3
#define		AIN4			0x4	// 选择外部电压输入脚AIN4
#define		AIN5			0x5	// 选择外部电压输入脚AIN5
#define		AIN6			0x6	// 选择外部电压输入脚AIN6
#define		AIN7			0x7	// 选择外部电压输入脚AIN7
#define 	AIN8			0x8	// 选择外部电压输入脚AIN8
#define		VDD4_1			0x9	// 选择内部电压输入 (4分之1 VDD)
#define		AIN_GND      	0xc	// 内部接地
/******************
 * 4th Argument
 * ****************/
// fcgck=16M... Conv256CLK(16us) ~ Conv1024CLK( 64us)
// fcgck= 8M... Conv128CLK(16us) ~ Conv1024CLK(128us)
// fcgck= 4M... Conv64CLK (16us) ~ Conv512CLK (128us)
// fcgck= 2M... Conv32CLK (16us) ~ Conv256CLK (128us)
#define		Conv32CLK		0x0	// AD转换时间-  32个齿轮时钟
#define		Conv64CLK		0x1	// AD转换时间-  64个齿轮时钟
#define		Conv128CLK		0x2	// AD转换时间- 128个齿轮时钟
#define		Conv256CLK		0x3	// AD转换时间- 256个齿轮时钟
#define		Conv512CLK		0x4	// AD转换时间- 512个齿轮时钟
#define		Conv1024CLK		0x5	// AD转换时间-1024个齿轮时钟
								// (*注意转换时间应设定在12.8 us ~ 128 us 范围内)
/******************
 * 5th Argument
 * ****************/
#define		Vref2			0x0	// 选择内部 2V参考电压
#define		Vref3			0x1	// 选择内部 3V参考电压
#define		Vref4			0x2	// 选择内部 4V参考电压
#define		VDDVref			0x3	// 选择内部VDD参考电压
#define		EXTVref			0x4	// 选择外部Ext参考电压，会使用与AIN3相同的第28脚(P43)作为
								// 外部参考电压输入，故设置外部参考电压时，不能使用AIN3作为外部电压输入


//-- 定义全局变数 --//
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


















