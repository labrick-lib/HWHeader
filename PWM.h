/*
˵����
1����PWMռ���˶�ʱ��1�ķ�ʽ2�������޸�
2��m,n��0~~7֮����ֹͣת����45���ҿ�ʼ����
   �ɵ���ΧΪ��+43~~+53��-43~~-53����
3��Wheel��0Ϊ���֣�1Ϊ����

ʹ�÷�����
1��#include<PWM.h>
2��ע�ⶨʱ��
3����IO�ڣ�������ţ�
4������T1Init();�������г�ʼ����ʱ��
3��ֱ�ӵ���void ADD(unsigned char Wheel)��void SUB(unsigned char Wheel)�������п��ƣ�����Wheel��0Ϊ���֣�1Ϊ���֣�
   ����ֱ��ʹ��m,n���Ƶ����ת��

*/
#ifndef _PWM_H_
#define _PWM_H_
#include<math.h>
#define SPEED 43
char m=4; 		//�������Ʊ���
char n=4;		//����ҿ��Ʊ���
char i;			//������жϱ���
char j;			//������жϱ���

sbit s1=P1^7;		//L298N��IN1
sbit s2=P1^6;	  	//L298N��IN2
sbit s3=P1^5;		//L298N��IN3
sbit s4=P1^4;	  	//L298N��IN4
//==========================��ʱ��1��ʽ2��ʼ��
void T1Init()
{
	ET1 = 1;
	EA =1;	  			//���ж�
	TMOD = 0x20;		//��ʱ���ж�����
	TH1 = 0xFE;
	TL1 = 0xFE;							  
	TR1 = 1;
}
//==============================����жϺ���
void motor() interrupt 3	  //�жϴٷ�
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
//=============================���ٺ���
void ADD(unsigned char Wheel)	//Wheel��0Ϊ���֣�1Ϊ����
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
//============================���ٺ���
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