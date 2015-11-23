/*
˵����12864����Ҫ�Ļ������ܺ���
1��1ms��ʱ������void Delay(unsigned int z)
2��дָ��:void WriteCom(unsigned char com)
3��д���ݣ�void WriteDat(unsigned char dat)
4����ʼ����void LCDInit()
5��˳����ʾ��void Display(unsigned char add,unsigned char *ch)	//��ַ ������
6����ֵ��ʾvoid DisplayValue(long int Value)	//���ָ�ʮ����ʾ
7��������Ծ��void Lcd_Pos(unsigned char X,unsigned char Y)	 //����λ��

ʹ�÷�����
1��#include<12864.h>
2����IO�ڣ���������
3��main�����м���LCDInit();��ʼ��
4��6��7Ĭ�ϱ�����
*/

#ifndef _12864_H_
#define _12864_H_
//=====================�궨��
#define Data P1
//=====================��������
//unsigned char code num[]="123456789";
unsigned char code ch1[]="  2011ȫ������";
unsigned char code ch2[]="�¶�ֵ��      ��";
unsigned char code ch3[]="����ֵ��      CM";
unsigned char code ch4[]="��ѹֵ��       V";

unsigned char Array[5];
//=====================λ����
sbit RS = P0^0;
sbit RW = P0^1;
sbit EN = P0^2;

#ifndef _DELAY_
#define _DELAY_
//=====================1ms��ʱ����
void Delay(unsigned int z)
{
	unsigned int a,b;
	for(a=0; a<z; a++)
		for(b=0; b<110; b++);
}
#endif
//=====================LCDд����
void WriteCom(unsigned char com)
{
	RS = 0;
	EN = 0;
	Data = com;
	Delay(5);
	EN = 1;
	Delay(5);
	EN = 0;
}
//=====================LCDд����
void WriteDat(unsigned char dat)
{
	RS = 1;
	EN = 0;
	Data = dat;
	Delay(5);
	EN = 1;
	Delay(5);
	EN = 0;	
}
//=====================LCD��ʼ��
void LCDInit()
{
	RW = 0;
	WriteCom(0x06);//�趨�α��ƶ�����ָ����ʾ����λ
	WriteCom(0x0c);//0000 1111������ʾ �α� �α�λ��
//	WriteCom(0x18);	//����ͼ������
	WriteCom(0x30);	//DL����Ϊ1 RE����ָ�
	WriteCom(0x01);
	WriteCom(0x02);	
}
//=====================��ַ˳����ʾ����
void Display(unsigned char add,unsigned char *ch)	//��ַ ������
{
	unsigned char i = 0;
	WriteCom(add);									//��ʾ��N��
	while( i<16 && *(ch+i)!='\0')
	{	
		WriteDat(*(ch+i++));
	}
	if(*(ch+i)!='\0')
	{
		WriteCom(add+0x10);							//��ʾ��N+1��
		while(i<32 && *(ch+i)!='\0')
			WriteDat(*(ch+i++));
	}
	if(*(ch+i)!='\0')
	{
		WriteCom(add+0x08);							//��ʾ��N+2��
		while(i<48 && *(ch+i)!='\0')
			WriteDat(*(ch+i++));
  	}
	if(*(ch+i)!='\0')
	{
		WriteCom(add+0x18);							//��ʾ��N+3��
		while(i<64 && *(ch+i)!='\0')
			WriteDat(*(ch+i++));
   	}
	if(*(ch+i)!='\0')
	{
		while(*(ch+i)!='\0')
			WriteDat(*(ch+i++));
	}
}
//===================LCD��ֵ��ʾģʽ
/*void DisplayValue(unsigned char add,long int Value)
{
	WriteCom(add);
	Array[0] = Value/1000 + '0';
	Array[1] = '.';
	Array[2] = Value%1000/100 + '0';
	Array[3] = Value%1000%100/10 + '0';
	Array[4] = Value%1000%100%10 + '0';
	WriteDat(Array[0]);
	WriteDat(Array[1]);
	WriteDat(Array[2]);
	WriteDat(Array[3]); 
	WriteDat(Array[4]);
}
//=======================ָ�������λ��
void Lcd_Pos(unsigned char X,unsigned char Y)	 //����λ��
{
    unsigned char pos;

 	if( X==0 )		{	X = 0x80;	}
    else if( X==1 )	{	X = 0x90;	}
    else if( X==2 )	{	X = 0x88;	}
    else if( X==3 )	{	X = 0x98;	}

    pos= X+Y;
    write_cmd(pos);
}*/
#endif