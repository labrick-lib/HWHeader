/*
ʹ�÷�����
1��#include<SMotor.h>
2��ֱ�ӵ���void SMotor(uint Angle,uint DTime,unsigned char Dir)	//�Ƕȣ���ʱʱ�䣬����0Ϊ��ת��1Ϊ��ת��

˵�����Ƕ����⣬����360����дΪ360*n+m��nȦ����m��ǣ�
	  ��ʱ��100---255֮�䣬���ʾ�������ת���ȶ�ʱת�����ٶȣ�ֵԽС�ٶ�Խ��
*/

#ifndef _SMOTOR_H_
#define _SMOTOR_h_
#include<intrins.h>
//=====================��������
unsigned char code table[8]={0x90,0x10,0x30,0x20,0x60,0x40,0xc0,0x80};    //��ʱ����ת�����

//=======================���������������
void SMotor(unsigned int Angle,unsigned int DTime,unsigned char Dir)	//�Ƕȣ���ʱʱ�䣬����0Ϊ��ת��1Ϊ��ת��
{
	 unsigned int i,j,x;
	 unsigned char DT=255;		//��ʱ����������ֵ�����ڲ������������Ƶ���Լ��ٻ��ֹʧ����
	 if(Dir == 0)
	 for( j=0; j<Angle/0.70588; j++)
	 {	
		 for( i=0; i<8; i++ ) 
		 {
		 	P1 &= 0x0F;			//���ε���λ����ֹӰ�츳ֵ
		 	P1 |= table[i];	  	//��ֵ���Ҹ���λ���仯
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