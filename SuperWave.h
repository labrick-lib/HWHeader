/*
˵������������������ʹ��
ʹ�÷�����
1��#include<SuperWave.h>
2����IO��
3��main()�����м���SWInit();��ʼ��
4����GetDis()������ó����������صľ��룬��λΪCM
*/
#ifndef _SUPERWAVE_H_
#define _SUPERWAVE_H_

//======================��������
sbit Trig =P0^3;
sbit Echo=P0^4;
//======================��������
uint Time;

#ifndef _DELAYUS_
#define _DELAYUS_
//======================1us��ʱ����
void Delayus(int num)//��ʱ����
{
    while(num--) ;
}
#endif
//======================������ռ��һ����ʱ�����Զ�ʱ�����г�ʼ��
void SWInit()
{
	TMOD=0x01;                   //��T0Ϊ��ʽ1��GATE=1��   
	EA=1;   //�������ж�      
	Trig=0;
}
//======================�������������
void StartModule()              //����ģ��
{
    Trig=1;                     //����һ��ģ��
	Delayus(300);				//20us
    Trig=0;
}
//=====================��ó��������ص����ݲ�����ת��
int GetDis()
{
	uint S;
//===========�������
	EA=0;
	StartModule();
	while(!Echo);        //��echoΪ��ʱ�ȴ�,�ж�flag������
	EA=1;
	ET0=1;
	TR0=1;				   //��������                  
	while(Echo);
	TR0=0;
//==========����ת��
    Time=(TH0*256+TL0);
    TH0=0;
    TL0=0;    
    S=(Time*1.7)/100;     //�������CM   
    return S;               
}
#endif