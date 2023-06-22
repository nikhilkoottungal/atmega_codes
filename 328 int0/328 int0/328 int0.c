/*
 * intrext.c
 *
 * Created: 19-Jan-17 3:14:59 PM
 *  Author: Njj
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect)
{
	
	PORTB=0xff;
	_delay_ms(1000);
	PORTB=0x00;
        _delay_ms(1000);
	EIFR=0x00;
	
}

int main(void)
{
	
	DDRB=0xff;
	
	DDRD=0xfb;
	PORTD=0xff;
	EICRA=0x00;
	EIMSK|=0x01;
	sei();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}