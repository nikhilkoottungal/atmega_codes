/*
 * GccApplication12.c
 *
 * Created: 18-Jan-17 8:19:07 PM
 *  Author: Njj
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

int count=0;
ISR(TIMER0_OVF_vect)
{
	
	count++;
	if(count==200)
	{
		
		PORTB=~PORTB;
		count=0;
	}
	TCNT0=177;
}


int main(void)
{
	
	
	DDRB=0xff;
	PORTB=0x00;
	sei();
	TCCR0B=0x05;
	TCNT0=177;
	TIMSK0=0x01;
	
    while(1);
    
     
}