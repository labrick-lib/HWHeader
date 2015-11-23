/*
使用方法：
1、#include<5410PWM.h>
2、PWMInit();初始化PWM波形
3、调用void AddSpeed(unsigned char Wheel)和void SubSpeed(unsigned char Wheel)电机控制函数控制电机
   Wheel:0表示左轮，1表示右轮
*/
#ifndef _5410PWM_H_
#define _5410PWM_H_

#define SValue 60
//=============================变量定义
sbit s1 = P1^7;		//左轮正
sbit s2 = P1^6;		//左轮负
sbit s3 = P1^5;		//右轮正
sbit s4 = P1^4;		//右轮负

unsigned int LEmpty = 80;
unsigned int REmpty = 80;
unsigned char flag1=0;	//0表示正转1表示反转
unsigned char flag2=0;
//=============================PWM初始化
/*和PWM0有关的寄存器
CCON:PCA控制寄存器
CMOD:PCA工作模式寄存器
CL	:PCA定时器低位初始值
CH	:PCA定时器高位初始值
CCAPM0:PCA模式0寄存器
CCAP0L:PCA模式0捕获寄存器低位
CCAP0H:PCA模式0捕获寄存器高位
PCA_PWM0:PCAPWM模式寄存器

sbit CF    = CCON^7;	//PCA计数器阵列溢出标志位 CMOD中ECF位决定其是否可用
sbit CR    = CCON^6;	//PCA计数器阵列运行控制位
sbit CCF5  = CCON^5;	//技术文档中无
sbit CCF4  = CCON^4;	//技术文档中无
sbit CCF3  = CCON^3;	//PCA模块3中断标志 下同
sbit CCF2  = CCON^2;
sbit CCF1  = CCON^1;
sbit CCF0  = CCON^0;
*/
//====================5410分频设置
//1-2T,2-4T,3-8T,4-16T,5-32T,6-64T,7-128T
void DivClk()
{
	CLK_DIV = 0x01;
}
void PWMInit()
{
	DivClk();
	CCON = 0;	//初始化PCA控制寄存器
				//PCA定时器停止运行
				//清零标志位
				//清零所有模式中断标志位
				//重置PCA基本定时器
	CL = 0x00;
	CH = 0x00;
	CMOD = 0x01;	//0000 0010 CPS1 CPS2 0 1设置PCA定时器时钟源为外部晶振2T
					//关闭PAC定时器溢出中断
	CCAP0H = CCAP0L = 256-LEmpty;	//PWM0端输出占空比50%方波	0x80为0xFF的一半
	CCAPM0 = 0x42;			//PCA模式0工作在8位PWM模式,且无PCA中断 ECOM0为1，PWM0为1 即为0x42
	
	CCAP1H = CCAP1L = 256-REmpty;	//PWM0端输出占空比50%方波	0x80为0xFF的一半
	CCAPM1 = 0x42;			//PCA模式0工作在8位PWM模式,且无PCA中断 ECOM0为1，PWM0为1 即为0x42
	CR = 1;			//PCA定时器启动	
}
//================================电机加速控制函数
void AddSpeed(unsigned char Wheel)
{
	if(Wheel==0)
	{
		if(LEmpty<=SValue)	{	flag1=0;LEmpty=SValue;	}
		if(flag1==0)		{	LEmpty++;s1=0;s2=1;	}	
		if(flag1==1)		{	LEmpty--;s1=1;s2=0;	}
		if(LEmpty>=255)		LEmpty=255;
		CCAP0H = CCAP0L = 256-LEmpty;	//PWM0端输出占空比50%方波	0x80为0xFF的一半
	}else if(Wheel==1)
	{
		if(REmpty<=SValue)	{	flag2=0;REmpty=SValue;	}
		if(flag2==0)		{	REmpty++;s3=0;s4=1;	}	
		if(flag2==1)		{	REmpty--;s3=1;s4=0;	}
		if(REmpty>=255)		REmpty=255;
		CCAP1H = CCAP1L = 256-REmpty;	//PWM0端输出占空比50%方波	0x80为0xFF的一半	
	}
}
//================================电机减速控制函数
void SubSpeed(unsigned char Wheel)
{
	if(Wheel==0)
	{
		if(LEmpty<=SValue)	{	flag1=1;LEmpty=SValue;	}
		if(flag1==0)		{	LEmpty--;s1=0;s2=1;	}
		if(flag1==1)		{	LEmpty++;s1=1;s2=0;	}		
		if(LEmpty>=255)		LEmpty=255;
		CCAP0H = CCAP0L = 256-LEmpty;	//PWM0端输出占空比50%方波	0x80为0xFF的一半
	}else if(Wheel==1)
	{
		if(REmpty<=SValue)	{	flag2=1;REmpty=SValue;	}
		if(flag2==0)		{	REmpty--;s3=0;s4=1;	}
		if(flag2==1)		{	REmpty++;s3=1;s4=0;	}		
		if(REmpty>=255)		REmpty=255;
		CCAP1H = CCAP1L = 256-REmpty;	//PWM0端输出占空比50%方波	0x80为0xFF的一半		
	}	
}
#endif