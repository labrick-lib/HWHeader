/*
˵����
�������ʾ�Ļ���������������Ҫ���ٵ�ɨ��

ʹ�÷�����
1��#include<Digital.h>
2����IO��
3��ֱ�ӵ���void Display(uint Count)����������ֵ����ʾ
*/
#ifndef _DIGTAL_H_
#define _DIGTAL_H_
//=====================�궨��
#define uint unsigned int
#define uchar unsigned char
#define DData P1
//=====================���Ŷ���
sbit dula = P3^6;
sbit wela = P3^7;
//=====================��������
uint num,i,count,qian,bai,shi,ge;
uchar flag,timer;

unsigned char code tabledu[] = {
		0x3f,0x06,0x5b,0x4f,
		0x66,0x6d,0x7d,0x07,
		0x7f,0x6f   };

unsigned char code tablewe[] = {
		~0x01,~0x02,~0x04,~0x08		};

#ifndef _DELAY_
#define _DELAY_
void Delay(uint z)
{
	uint i,k;
	for( k=0; k<z; k++)
			for( i=0; i<130; i++);
}
#endif
				
void Display(uint Count)
{
//===============�������
	qian = Count/1000;
	bai = Count%1000/100;
	shi = Count%1000%100/10;
	ge = Count%1000%100%10;
//===============������ʾ
	DData = 0x00;					   //������ǰ�����ݣ��أ�
	dula =1;
	DData = tabledu[qian];			   //������dula��wela ������
	dula = 0;
	wela =1;
	DData = tablewe[0];
	wela = 0;
//	dula =1;
//	DData = tabledu[qian];			   // ������
//	dula = 0;
	Delay(1);

	wela =1;					   //������wela��dula ������
	DData = tablewe[1];
	wela = 0;
	dula =1;
	DData = tabledu[bai];
	dula = 0;
	Delay(1);

	wela =1;					   //ͬ��
	DData = tablewe[2];
	wela = 0;
	dula =1;
	DData = tabledu[shi];
	dula = 0;
	Delay(1);

	wela =1;					   //�������ڣ�������
	DData = tablewe[3];
	wela = 0;
	dula =1;
	DData = tabledu[ge];
	dula = 0;
	Delay(1);
} 
#endif