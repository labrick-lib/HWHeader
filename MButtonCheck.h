/*
˵����
�������uchar MButtonCheck()�Ǵ��з���ֵk���Ӻ���
k���ڶ��ٴ����Ǹ�����������

ʹ�÷�����
1��#include<MButtonCheck.h>
2����IO��
3������ѡ��unsigned char temp,k;ָ����ڸú����ڲ��൱�ڡ�����������,�����ڿ��ƣ�Ĭ�ϣ�
						  ָ����ڸú����ⲿ�൱�ڡ�����ʽ������
3��ֱ�ӵ���MButtonCheck()�Ӻ������Kֵ
*/
#ifndef _MBUTTONCHECK_H_
#define _MBUTTONCHECK_H_
#define MP P2

//unsigned char temp,k;			//����ʽ����
//=====================������̼��
unsigned char MButtonCheck()
{
	unsigned char temp,k=0;		//����������Ĭ��		
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
			temp = 0xFE;		//��������ѭ��
			while(MP!=0xFE);	//���ּ��
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
			temp = 0xFD;		//��������ѭ��
			while(MP!=0xFD);	//���ּ��
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
			temp = 0xFB;		//��������ѭ��
			while(MP!=0xFB);	//���ּ��
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
			temp = 0xF7;		//��������ѭ��
			while(MP!=0xF7);	//���ּ��
		}
	}
	return k;
}
#endif