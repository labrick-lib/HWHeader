/*
说明：超声波传感器的使用
使用方法：
1、#include<SuperWave.h>
2、改IO口
3、main()函数中加入SWInit();初始化
4、用GetDis()函数获得超声波所返回的距离，单位为CM
*/
#ifndef _SUPERWAVE_H_
#define _SUPERWAVE_H_

//======================定义引脚
sbit Trig =P0^3;
sbit Echo=P0^4;
//======================变量定义
uint Time;

#ifndef _DELAYUS_
#define _DELAYUS_
//======================1us延时函数
void Delayus(int num)//延时函数
{
    while(num--) ;
}
#endif
//======================超声波占用一个定时器，对定时器进行初始化
void SWInit()
{
	TMOD=0x01;                   //设T0为方式1，GATE=1；   
	EA=1;   //开启总中断      
	Trig=0;
}
//======================启动超声波测距
void StartModule()              //启动模块
{
    Trig=1;                     //启动一次模块
	Delayus(300);				//20us
    Trig=0;
}
//=====================获得超声波传回的数据并进行转换
int GetDis()
{
	uint S;
//===========获得数据
	EA=0;
	StartModule();
	while(!Echo);        //当echo为零时等待,中断flag跳出等
	EA=1;
	ET0=1;
	TR0=1;				   //开启计数                  
	while(Echo);
	TR0=0;
//==========数据转换
    Time=(TH0*256+TL0);
    TH0=0;
    TL0=0;    
    S=(Time*1.7)/100;     //算出来是CM   
    return S;               
}
#endif