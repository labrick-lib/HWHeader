/*
说明：
直线步进电机，螺纹之间最小距离为8mm，而50个脉冲循环是一圈。即：H*6.25得到需要的脉冲数，其中H为要变化的高度
使用方法：
1、#include<SSMotor.h>
2、改IO口
3、直接调用void SSMotor(uint High,uint DTime,unsigned char Dir)	//变化高度，延时时间，方向（0为上升，1为下降）

说明：高度为1~100之间的一个数值，单位为mm
	  延时在100---500之间，其表示直线步进电机转轴稳定时转动的速度，值越小速度越快
*/

#ifndef _SMOTOR_H_
#define _SMOTOR_h_
#include<intrins.h>
#define SData P0
//=====================变量定义
unsigned char code table[]={0x10,0x50,0x40,0x60,0x20,0xa0,0x80,0x90};

//=======================步进电机驱动程序
void SSMotor(unsigned int High,unsigned int DTime,unsigned char Dir)	//角度，延时时间，方向（0为正转，1为倒转）
{
	 unsigned int i,j,x;
	 unsigned int DT=255;		//延时函数的启动值（调节步进电机的启动频率以加速或防止失步）
	 if(Dir == 0)
	 for( j=0; j<High*6.25; j++)
	 {	
		 for( i=0; i<8; i++ ) 
		 {
		 	SData &= 0x0F;			//屏蔽低四位，防止影响赋值
		 	SData |= table[i];	  	//赋值并且高四位不变化
			for( x=0; x<DT; x++)
			_nop_();
		 }
		 if(--DT<DTime)	DT=DTime;
	 }
	 if(Dir == 1)
	 for( j=0; j<High*6.25; j++)
	 {
		 for( i=8; i>0; i-- ) 
		 {
		 	SData &= 0x0F;
		 	SData |= table[i];
			for( x=0; x<DT; x++)
			_nop_();
		 }
		 if(--DT<DTime)	DT=DTime;
	 }
}
#endif 