/*
说明：
1、该PWM占用了定时器1的方式2，妥善修改
2、m,n在0~~7之间电机停止转动，45左右开始启动
   可调范围为：+43~~+53，-43~~-53左右
3、Wheel：0为左轮，1为右轮

使用方法：
1、#include<PWM.h>
2、注意定时器
3、改IO口（电机引脚）
4、调用T1Init();函数进行初始化定时器
3、直接调用void ADD(unsigned char Wheel)和void SUB(unsigned char Wheel)函数进行控制（其中Wheel：0为左轮，1为右轮）
   或者直接使用m,n控制电机的转动

*/
#ifndef _PWM_H_
#define _PWM_H_
#include<math.h>
#define SPEED 43
char m=4; 		//电机左控制变量
char n=4;		//电机右控制变量
char i;			//电机左中断变量
char j;			//电机右中断变量

sbit s1=P1^7;		//L298N中IN1
sbit s2=P1^6;	  	//L298N中IN2
sbit s3=P1^5;		//L298N中IN3
sbit s4=P1^4;	  	//L298N中IN4
//==========================定时器1方式2初始化
void T1Init()
{
	ET1 = 1;
	EA =1;	  			//总中断
	TMOD = 0x20;		//定时器中断设置
	TH1 = 0xFE;
	TL1 = 0xFE;							  
	TR1 = 1;
}
//==============================电机中断函数
void motor() interrupt 3	  //中断促发
{
	i++;j++;	
	if(m>0)
	{
		if(i>=3)	{s1=1;s2=0;}	
		if(i>=m)	{i=0;s1=0;s2=0;}
	}
	if(m<0)
	{
		if(i>=3)	{s2=1;s1=0;}	
		if(abs(i)>=abs(m))	{i=0;s1=0;s2=0;}
	}

	if(n>0)
	{
		if(j>=3)	{s3=1;s4=0;}	
		if(j>=n)	{j=0;s3=0;s4=0;}
	}
	if(n<0)
	{
		if(j>=3)	{s4=1;s3=0;}	
		if(abs(j)>=abs(n))	{j=0;s3=0;s4=0;}
	}
}
//=============================加速函数
void ADD(unsigned char Wheel)	//Wheel：0为左轮，1为右轮
{
	if(Wheel==0)
	{
		m++;
		if(m>-SPEED && m<SPEED)		m=SPEED;
	}
	else if(Wheel==1)
	{
		n++;
		if(n>-SPEED && n<SPEED)		n=SPEED;
	}	
}
//============================减速函数
void SUB(unsigned char Wheel)
{
	if(Wheel==0)
	{
		m--;
		if(m<SPEED && m>-SPEED)		m=-SPEED;
	}
	else if(Wheel==1)
	{
		n--;
		if(n<SPEED && n>-SPEED)		n=-SPEED;
	}	
}
#endif