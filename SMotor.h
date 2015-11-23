/*
使用方法：
1、#include<SMotor.h>
2、直接调用void SMotor(uint Angle,uint DTime,unsigned char Dir)	//角度，延时时间，方向（0为正转，1为倒转）

说明：角度任意，大于360可以写为360*n+m（n圈数，m余角）
	  延时在100---255之间，其表示步进电机转轴稳定时转动的速度，值越小速度越快
*/

#ifndef _SMOTOR_H_
#define _SMOTOR_h_
#include<intrins.h>
//=====================变量定义
unsigned char code table[8]={0x90,0x10,0x30,0x20,0x60,0x40,0xc0,0x80};    //正时钟旋转相序表

//=======================步进电机驱动程序
void SMotor(unsigned int Angle,unsigned int DTime,unsigned char Dir)	//角度，延时时间，方向（0为正转，1为倒转）
{
	 unsigned int i,j,x;
	 unsigned char DT=255;		//延时函数的启动值（调节步进电机的启动频率以加速或防止失步）
	 if(Dir == 0)
	 for( j=0; j<Angle/0.70588; j++)
	 {	
		 for( i=0; i<8; i++ ) 
		 {
		 	P1 &= 0x0F;			//屏蔽低四位，防止影响赋值
		 	P1 |= table[i];	  	//赋值并且高四位不变化
			for( x=0; x<DT; x++)
			_nop_();
		 }
		 if(--DT<DTime)	DT=DTime;
	 }
	 if(Dir == 1)
	 for( j=0; j<Angle/0.70588; j++)
	 {
		 for( i=8; i>0; i-- ) 
		 {
		 	P1 &= 0x0F;
		 	P1 |= table[i];
			for( x=0; x<DT; x++)
			_nop_();
		 }
		 if(--DT<DTime)	DT=DTime;
	 }
}
#endif 