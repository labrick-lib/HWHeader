/*
说明：温度传感器的使用
使用方法：
1、#include<TEMPERATURE.h>
2、改IO口
3、用GetTemp()函数获得当前温度值，单位为度*10（放大10倍）
*/

#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

//=======================引脚定义
sbit DQ=P0^5;

#ifndef _DELAYUS_
#define _DELAYUS_
//======================1us延时函数
void Delayus(int num)//延时函数
{
    while(num--) ;
}
#endif 
//=======================DS18B20初始化函数
void DS18B20Init()
{
    DQ = 1;    			//DQ复位
    Delayus(8);  		//稍做延时
    DQ = 0;    			//单片机将DQ拉低
    Delayus(90); 		//精确延时 大于 480us
    DQ = 1;    			//拉高总线
    Delayus(20);
}
//=======================读一个字节
uchar ReadOneChar()
{
    uchar i=0;
    uchar dat = 0;
    for (i=8;i>0;i--)
    {
        DQ = 0;		 		// 给脉冲信号
        dat>>=1;
        DQ = 1; 			// 给脉冲信号
        if(DQ)
        dat|=0x80;
        Delayus(4);
    }
    return(dat);
}
//=======================写一个字节
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
//========================读取温度
uint GetTemp()
{
    uchar a=0;
    uchar b=0;
    uint t=0;
    float tt=0;
	    
    DS18B20Init();
    WriteOneChar(0xCC); // 跳过读序号列号的操作
    WriteOneChar(0x44); // 启动温度转换
    DS18B20Init();
    WriteOneChar(0xCC); //跳过读序号列号的操作
    WriteOneChar(0xBE); //读取温度寄存器
    a=ReadOneChar();   //连续读两个字节数据   //读低8位 
    b=ReadOneChar();                          //读高8位
    t=b;
    t<<=8;
    t=t|a;		 	//两字节合成一个整型变量。
    tt=t*0.0625;  	//得到真实十进制温度值，因为DS18B20可以精确到0.0625度，所以读回数据的最低位代表的是0.0625度
    t= tt*10+0.5; 	//放大十倍，这样做的目的将小数点后第一位也转换为可显示数字，同时进行一个四舍五入操作。
    return(t);
}
#endif