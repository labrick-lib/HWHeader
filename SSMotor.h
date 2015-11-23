/*
˵����
ֱ�߲������������֮����С����Ϊ8mm����50������ѭ����һȦ������H*6.25�õ���Ҫ��������������HΪҪ�仯�ĸ߶�
ʹ�÷�����
1��#include<SSMotor.h>
2����IO��
3��ֱ�ӵ���void SSMotor(uint High,uint DTime,unsigned char Dir)	//�仯�߶ȣ���ʱʱ�䣬����0Ϊ������1Ϊ�½���

˵�����߶�Ϊ1~100֮���һ����ֵ����λΪmm
	  ��ʱ��100---500֮�䣬���ʾֱ�߲������ת���ȶ�ʱת�����ٶȣ�ֵԽС�ٶ�Խ��
*/

#ifndef _SMOTOR_H_
#define _SMOTOR_h_
#include<intrins.h>
#define SData P0
//=====================��������
unsigned char code table[]={0x10,0x50,0x40,0x60,0x20,0xa0,0x80,0x90};

//=======================���������������
void SSMotor(unsigned int High,unsigned int DTime,unsigned char Dir)	//�Ƕȣ���ʱʱ�䣬����0Ϊ��ת��1Ϊ��ת��
{
	 unsigned int i,j,x;
	 unsigned int DT=255;		//��ʱ����������ֵ�����ڲ������������Ƶ���Լ��ٻ��ֹʧ����
	 if(Dir == 0)
	 for( j=0; j<High*6.25; j++)
	 {	
		 for( i=0; i<8; i++ ) 
		 {
		 	SData &= 0x0F;			//���ε���λ����ֹӰ�츳ֵ
		 	SData |= table[i];	  	//��ֵ���Ҹ���λ���仯
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