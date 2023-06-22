/*
 * GccApplication5.c
 *
 * Created: 17-Jan-17 7:34:19 PM
 *  Author: Njj
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
   DDRC=0xff;
   char disarray[10]={0x02,0x9E,0x24,0x0C,0x98,0x48,0x40,0x1E,0x00,0x08};
	while(1)
	{
		for(int i=0;i<10;i++)
	{
		PORTC=disarray[i];
		_delay_ms(1000);
	}		   
	}	   
}