/*
说明：
数码管显示的基本函数，不过需要快速的扫描

使用方法：
1、#include<Digital.h>
2、改IO口
3、直接调用void Display(uint Count)函数进行数值的显示
*/
#ifndef _DIGTAL_H_
#define _DIGTAL_H_
//=====================宏定义
#define uint unsigned int
#define uchar unsigned char
#define DData P1
//=====================引脚定义
sbit dula = P3^6;
sbit wela = P3^7;
//=====================变量定义
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
//===============拆分数据
	qian = Count/1000;
	bai = Count%1000/100;
	shi = Count%1000%100/10;
	ge = Count%1000%100%10;
//===============进行显示
	DData = 0x00;					   //清零以前的内容（重）
	dula =1;
	DData = tabledu[qian];			   //必须先dula后wela ？？？
	dula = 0;
	wela =1;
	DData = tablewe[0];
	wela = 0;
//	dula =1;
//	DData = tabledu[qian];			   // ？？？
//	dula = 0;
	Delay(1);

	wela =1;					   //必须先wela后dula ？？？
	DData = tablewe[1];
	wela = 0;
	dula =1;
	DData = tabledu[bai];
	dula = 0;
	Delay(1);

	wela =1;					   //同上
	DData = tablewe[2];
	wela = 0;
	dula =1;
	DData = tabledu[shi];
	dula = 0;
	Delay(1);

	wela =1;					   //问题所在？？？？
	DData = tablewe[3];
	wela = 0;
	dula =1;
	DData = tabledu[ge];
	dula = 0;
	Delay(1);
} 
#endif