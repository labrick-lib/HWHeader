/*
˵�����¶ȴ�������ʹ��
ʹ�÷�����
1��#include<TEMPERATURE.h>
2����IO��
3����GetTemp()������õ�ǰ�¶�ֵ����λΪ��*10���Ŵ�10����
*/

#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

//=======================���Ŷ���
sbit DQ=P0^5;

#ifndef _DELAYUS_
#define _DELAYUS_
//======================1us��ʱ����
void Delayus(int num)//��ʱ����
{
    while(num--) ;
}
#endif 
//=======================DS18B20��ʼ������
void DS18B20Init()
{
    DQ = 1;    			//DQ��λ
    Delayus(8);  		//������ʱ
    DQ = 0;    			//��Ƭ����DQ����
    Delayus(90); 		//��ȷ��ʱ ���� 480us
    DQ = 1;    			//��������
    Delayus(20);
}
//=======================��һ���ֽ�
uchar ReadOneChar()
{
    uchar i=0;
    uchar dat = 0;
    for (i=8;i>0;i--)
    {
        DQ = 0;		 		// �������ź�
        dat>>=1;
        DQ = 1; 			// �������ź�
        if(DQ)
        dat|=0x80;
        Delayus(4);
    }
    return(dat);
}
//=======================дһ���ֽ�
void WriteOneChar(uchar dat)
{
    uchar i=0;
    for (i=8; i>0; i--)
    {
        DQ = 0;
        DQ = dat&0x01;
        Delayus(5);
        DQ = 1;
        dat>>=1;
    }
}
//========================��ȡ�¶�
uint GetTemp()
{
    uchar a=0;
    uchar b=0;
    uint t=0;
    float tt=0;
	    
    DS18B20Init();
    WriteOneChar(0xCC); // ����������кŵĲ���
    WriteOneChar(0x44); // �����¶�ת��
    DS18B20Init();
    WriteOneChar(0xCC); //����������кŵĲ���
    WriteOneChar(0xBE); //��ȡ�¶ȼĴ���
    a=ReadOneChar();   //�����������ֽ�����   //����8λ 
    b=ReadOneChar();                          //����8λ
    t=b;
    t<<=8;
    t=t|a;		 	//���ֽںϳ�һ�����ͱ�����
    tt=t*0.0625;  	//�õ���ʵʮ�����¶�ֵ����ΪDS18B20���Ծ�ȷ��0.0625�ȣ����Զ������ݵ����λ�������0.0625��
    t= tt*10+0.5; 	//�Ŵ�ʮ������������Ŀ�Ľ�С������һλҲת��Ϊ����ʾ���֣�ͬʱ����һ���������������
    return(t);
}
#endif