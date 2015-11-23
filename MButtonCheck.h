/*
说明：
矩阵键盘uchar MButtonCheck()是带有返回值k的子函数
k等于多少代表那个按键被按下

使用方法：
1、#include<MButtonCheck.h>
2、改IO口
3、功能选择：unsigned char temp,k;指令放在该函数内部相当于“常开按键”,常用于控制（默认）
						  指令放在该函数外部相当于“自锁式按键”
3、直接调用MButtonCheck()子函数或的K值
*/
#ifndef _MBUTTONCHECK_H_
#define _MBUTTONCHECK_H_
#define MP P2

//unsigned char temp,k;			//自锁式按键
//=====================矩阵键盘检测
unsigned char MButtonCheck()
{
	unsigned char temp,k=0;		//常开按键，默认		
	MP = 0xFE;
	temp = MP;
	temp = temp&0xFE;
	while(temp!=0xFE)
	{
		temp = MP;
		temp = temp&0xFE;
		while(temp!=0xFE)
		{
			switch(temp)
			{		
				case 0xEE:	k = 1;	break;
				case 0xDE:	k = 2;	break;
				case 0xBE:	k = 3;	break;
				case 0x7E:	k = 4;	break;
			}
			temp = 0xFE;		//帮助跳出循环
			while(MP!=0xFE);	//松手检测
		}		
	}
	MP = 0xFD;
	temp = MP;
	temp = temp&0xFD;
	while(temp!=0xFD)
	{
		temp = MP;
		temp = temp&0xFD;
		while(temp!=0xFD)
		{
			switch(temp)
			{		
				case 0xED:	k = 5;	break;
				case 0xDD:	k = 6;	break;
				case 0xBD:	k = 7;	break;
				case 0x7D:	k = 8;	break;
			}
			temp = 0xFD;		//帮助跳出循环
			while(MP!=0xFD);	//松手检测
		}
	}
	MP = 0xFB;
	temp = MP;
	temp = temp&0xFB;
	while(temp!=0xFB)
	{
		temp = MP;
		temp = temp&0xFB;
		while(temp!=0xFB)
		{
			switch(temp)
			{		
				case 0xEB:	k = 9;	break;
				case 0xDB:	k = 10;	break;
				case 0xBB:	k = 11;	break;
				case 0x7B:	k = 12;	break;
			}
			temp = 0xFB;		//帮助跳出循环
			while(MP!=0xFB);	//松手检测
		}
	}
	MP = 0xF7;
	temp = MP;
	temp = temp&0xF7;
	while(temp!=0xF7)
	{
		temp = MP;
		temp = temp&0xF7;
		while(temp!=0xF7)
		{
			switch(temp)
			{		
				case 0xE7:	k = 13;	break;
				case 0xD7:	k = 14;	break;
				case 0xB7:	k = 15;	break;
				case 0x77:	k = 16;	break;
			}
			temp = 0xF7;		//帮助跳出循环
			while(MP!=0xF7);	//松手检测
		}
	}
	return k;
}
#endif