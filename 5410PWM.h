/*
ʹ�÷�����
1��#include<5410PWM.h>
2��PWMInit();��ʼ��PWM����
3������void AddSpeed(unsigned char Wheel)��void SubSpeed(unsigned char Wheel)������ƺ������Ƶ��
   Wheel:0��ʾ���֣�1��ʾ����
*/
#ifndef _5410PWM_H_
#define _5410PWM_H_

#define SValue 60
//=============================��������
sbit s1 = P1^7;		//������
sbit s2 = P1^6;		//���ָ�
sbit s3 = P1^5;		//������
sbit s4 = P1^4;		//���ָ�

unsigned int LEmpty = 80;
unsigned int REmpty = 80;
unsigned char flag1=0;	//0��ʾ��ת1��ʾ��ת
unsigned char flag2=0;
//=============================PWM��ʼ��
/*��PWM0�йصļĴ���
CCON:PCA���ƼĴ���
CMOD:PCA����ģʽ�Ĵ���
CL	:PCA��ʱ����λ��ʼֵ
CH	:PCA��ʱ����λ��ʼֵ
CCAPM0:PCAģʽ0�Ĵ���
CCAP0L:PCAģʽ0����Ĵ�����λ
CCAP0H:PCAģʽ0����Ĵ�����λ
PCA_PWM0:PCAPWMģʽ�Ĵ���

sbit CF    = CCON^7;	//PCA���������������־λ CMOD��ECFλ�������Ƿ����
sbit CR    = CCON^6;	//PCA�������������п���λ
sbit CCF5  = CCON^5;	//�����ĵ�����
sbit CCF4  = CCON^4;	//�����ĵ�����
sbit CCF3  = CCON^3;	//PCAģ��3�жϱ�־ ��ͬ
sbit CCF2  = CCON^2;
sbit CCF1  = CCON^1;
sbit CCF0  = CCON^0;
*/
//====================5410��Ƶ����
//1-2T,2-4T,3-8T,4-16T,5-32T,6-64T,7-128T
void DivClk()
{
	CLK_DIV = 0x01;
}
void PWMInit()
{
	DivClk();
	CCON = 0;	//��ʼ��PCA���ƼĴ���
				//PCA��ʱ��ֹͣ����
				//�����־λ
				//��������ģʽ�жϱ�־λ
				//����PCA������ʱ��
	CL = 0x00;
	CH = 0x00;
	CMOD = 0x01;	//0000 0010 CPS1 CPS2 0 1����PCA��ʱ��ʱ��ԴΪ�ⲿ����2T
					//�ر�PAC��ʱ������ж�
	CCAP0H = CCAP0L = 256-LEmpty;	//PWM0�����ռ�ձ�50%����	0x80Ϊ0xFF��һ��
	CCAPM0 = 0x42;			//PCAģʽ0������8λPWMģʽ,����PCA�ж� ECOM0Ϊ1��PWM0Ϊ1 ��Ϊ0x42
	
	CCAP1H = CCAP1L = 256-REmpty;	//PWM0�����ռ�ձ�50%����	0x80Ϊ0xFF��һ��
	CCAPM1 = 0x42;			//PCAģʽ0������8λPWMģʽ,����PCA�ж� ECOM0Ϊ1��PWM0Ϊ1 ��Ϊ0x42
	CR = 1;			//PCA��ʱ������	
}
//================================������ٿ��ƺ���
void AddSpeed(unsigned char Wheel)
{
	if(Wheel==0)
	{
		if(LEmpty<=SValue)	{	flag1=0;LEmpty=SValue;	}
		if(flag1==0)		{	LEmpty++;s1=0;s2=1;	}	
		if(flag1==1)		{	LEmpty--;s1=1;s2=0;	}
		if(LEmpty>=255)		LEmpty=255;
		CCAP0H = CCAP0L = 256-LEmpty;	//PWM0�����ռ�ձ�50%����	0x80Ϊ0xFF��һ��
	}else if(Wheel==1)
	{
		if(REmpty<=SValue)	{	flag2=0;REmpty=SValue;	}
		if(flag2==0)		{	REmpty++;s3=0;s4=1;	}	
		if(flag2==1)		{	REmpty--;s3=1;s4=0;	}
		if(REmpty>=255)		REmpty=255;
		CCAP1H = CCAP1L = 256-REmpty;	//PWM0�����ռ�ձ�50%����	0x80Ϊ0xFF��һ��	
	}
}
//================================������ٿ��ƺ���
void SubSpeed(unsigned char Wheel)
{
	if(Wheel==0)
	{
		if(LEmpty<=SValue)	{	flag1=1;LEmpty=SValue;	}
		if(flag1==0)		{	LEmpty--;s1=0;s2=1;	}
		if(flag1==1)		{	LEmpty++;s1=1;s2=0;	}		
		if(LEmpty>=255)		LEmpty=255;
		CCAP0H = CCAP0L = 256-LEmpty;	//PWM0�����ռ�ձ�50%����	0x80Ϊ0xFF��һ��
	}else if(Wheel==1)
	{
		if(REmpty<=SValue)	{	flag2=1;REmpty=SValue;	}
		if(flag2==0)		{	REmpty--;s3=0;s4=1;	}
		if(flag2==1)		{	REmpty++;s3=1;s4=0;	}		
		if(REmpty>=255)		REmpty=255;
		CCAP1H = CCAP1L = 256-REmpty;	//PWM0�����ռ�ձ�50%����	0x80Ϊ0xFF��һ��		
	}	
}
#endif