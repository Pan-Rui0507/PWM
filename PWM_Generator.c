#include "c8051f020.h"
#include <keyboard.h>
/* 	
		ʹ��T2�Զ���װ
		ϵͳʱ��2��Ƶ������
		ռ�ձȿɵ���1-99%��Ƶ�ʿɵ�
		��fre = 100ʱ��f = 10khz / 100 = 100Hz 
		duty1��Ӧ����
		duty2��Ӧ����
*/

sbit PWM = P1^0;
sbit GND = P1^1;
sbit PWM1 = P1^2;
sbit GND1 = P1^3;
bit wave1;
bit wave2;

unsigned char f = 0;	
static unsigned char duty1;			//ռ�ձ�
static unsigned char duty2;

void PWM_Init(unsigned int fre)
{	
	unsigned int t = 10000 / fre;
	ET2 = 1;
	CKCON |= 0x00; 	//12��Ƶ
	T2CON = 0x00;
	TR2 = 1;
	TH2 = (65536 - t) / 256;		//0.1ms --> 10KHz
	TL2 = (65536 - t) % 256;
	RCAP2H=(65536 - t)/256;
	RCAP2L=(65536 - t)%256;	
}

void Dir_Change()
{
	if(Dir)
	{
		PWM = wave1;
		GND = 0;
		PWM1 = wave2;
		GND1 = 0;
	}
	else 
	{
		PWM = 0;
		GND = wave1;
		PWM1 = 0;
		GND1 = wave2;
	}
}

void duty1_set(unsigned char d1)
{
	duty1 = d1;
}

void duty2_set(unsigned char d2)
{	
	duty2 = d2;
}

void duty_reset()
{
	duty1 = 50;
	duty2 = 50;
}

void duty1_alter(bit mode)
{
	if(duty1>0 && duty1 < 100)
	{
		if(!mode)
		{
			//duty1 = duty1 - 10;
			duty1 = 20;
		}
		else
		{//duty1 = duty1 + 10;
			duty1 = 80;
		}
	}
}

void duty2_alter(bit mode)
{
	if(duty2>0 && duty2 < 100)
	{
		if(!mode)
		{
			//duty1 = duty1 - 10;
			duty2 = 20;
		}
		else
		{//duty1 = duty1 + 10;
			duty2 = 80;
		}
	}
}
void PWM_generator() interrupt 5
{
	f++;
	TF2 = 0;
	if(f == duty1)
		wave1 = 0;
	if(f == duty2)
		wave2 = 0;
	if(f > 100)			
	{
		wave1 = 1;
		wave2 = 1;
		f = 0;
	}
	Dir_Change();
}

