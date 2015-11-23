/*
说明：12864所需要的基本功能函数
1、1ms延时函数：void Delay(unsigned int z)
2、写指令:void WriteCom(unsigned char com)
3、写数据：void WriteDat(unsigned char dat)
4、初始化：void LCDInit()
5、顺序显示：void Display(unsigned char add,unsigned char *ch)	//地址 数组名
6、数值显示void DisplayValue(long int Value)	//划分个十百显示
7、坐标跳跃：void Lcd_Pos(unsigned char X,unsigned char Y)	 //坐标位置

使用方法：
1、#include<12864.h>
2、改IO口，变量参数
3、main函数中加入LCDInit();初始化
4、6、7默认被屏蔽
*/

#ifndef _12864_H_
#define _12864_H_
//=====================宏定义
#define Data P1
//=====================变量定义
//unsigned char code num[]="123456789";
unsigned char code ch1[]="  2011全国电赛";
unsigned char code ch2[]="温度值：      ℃";
unsigned char code ch3[]="距离值：      CM";
unsigned char code ch4[]="电压值：       V";

unsigned char Array[5];
//=====================位定义
sbit RS = P0^0;
sbit RW = P0^1;
sbit EN = P0^2;

#ifndef _DELAY_
#define _DELAY_
//=====================1ms延时函数
void Delay(unsigned int z)
{
	unsigned int a,b;
	for(a=0; a<z; a++)
		for(b=0; b<110; b++);
}
#endif
//=====================LCD写命令
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
//=====================LCD写数据
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
//=====================LCD初始化
void LCDInit()
{
	RW = 0;
	WriteCom(0x06);//设定游标移动方向及指定显示的移位
	WriteCom(0x0c);//0000 1111整体显示 游标 游标位置
//	WriteCom(0x18);	//整体图像左移
	WriteCom(0x30);	//DL必须为1 RE扩充指令集
	WriteCom(0x01);
	WriteCom(0x02);	
}
//=====================地址顺序显示函数
void Display(unsigned char add,unsigned char *ch)	//地址 数组名
{
	unsigned char i = 0;
	WriteCom(add);									//显示第N行
	while( i<16 && *(ch+i)!='\0')
	{	
		WriteDat(*(ch+i++));
	}
	if(*(ch+i)!='\0')
	{
		WriteCom(add+0x10);							//显示第N+1行
		while(i<32 && *(ch+i)!='\0')
			WriteDat(*(ch+i++));
	}
	if(*(ch+i)!='\0')
	{
		WriteCom(add+0x08);							//显示第N+2行
		while(i<48 && *(ch+i)!='\0')
			WriteDat(*(ch+i++));
  	}
	if(*(ch+i)!='\0')
	{
		WriteCom(add+0x18);							//显示第N+3行
		while(i<64 && *(ch+i)!='\0')
			WriteDat(*(ch+i++));
   	}
	if(*(ch+i)!='\0')
	{
		while(*(ch+i)!='\0')
			WriteDat(*(ch+i++));
	}
}
//===================LCD数值显示模式
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
//=======================指定坐标的位置
void Lcd_Pos(unsigned char X,unsigned char Y)	 //坐标位置
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