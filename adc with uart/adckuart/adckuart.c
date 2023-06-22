/*
 * GccApplication2.c
 *
 * Created: 16-Jan-17 4:59:31 PM
 *  Author: Njj
 */ 

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


volatile unsigned char value;

ISR(USART_RXC_vect)
{
	
	value=UDR;
	UCSRA=0x40;
	UDR=value+1;
	while((UCSRA & 0x40)==0);
}


void send_char(volatile unsigned char c)
{
	
	UCSRA=0x40;
	UDR=c;
	while((UCSRA & 0x40)==0);
}



void prints(char *ptr)
{
	
	while(*ptr)
	{
		
		send_char(*ptr);
		ptr++;
	}
}


void dtoa(unsigned int val,char *buf,char n)
{
	
	buf[n]=0;
	while(n-->0)
	{
		
		buf[n]=(val%10)+'0';
		val=val/10;
	}
}


int read_adc(int chn)
{
	int val,val1;
	ADMUX=(0x40|(chn & 0x07));
	ADCSRA=0x85;
	_delay_us(10);
	ADCSRA|=0x40;
	while((ADCSRA & 0x40)==0x40);
	{
		
		val=ADCL;
		val1=ADCH;
		val|=(val1<<8);
		return(val);
	}
}







int main(void)
{
	float a=0;
	char dispbuf[5];
	UBRRH=0;
	UBRRL=103;
	
	UCSRA=0x00;
	UCSRB=0x98;
	UCSRC=0x86;
	sei();
	//prints("hello");
	
    while(1)
    {
       a=4.88*read_adc(2);
	    dtoa(a,dispbuf,5);
		prints(dispbuf);
		prints("\r \n");
		_delay_ms(500);
    }
}