/*
 * spiinterface.c
 *
 * Created: 21-Jan-17 10:35:00 AM
 *  Author: Njj
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>


#define DD_MOSI DDB5
#define DD_SCK DDB7
#define DD_SS DDB4
#define DDR_SPI DDRB

char number[13]={0x00,0xcf,0x92,0x86,0x42,0x26,0x22,0x8f,0x02,0x06,0x06,0x03};


void SPI_masterInit()
{
	
	DDR_SPI =(1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<CPOL);//0x5c
}

void SPI_masterTransmit(char data)
{
	SPDR=data;
	while((SPSR & 0x80)==0);
	
	
}
int main(void)
{
	
	
	char loc=0;
	SPI_masterInit();
    while(1)
    {
        //TODO:: Please write your application code 
		while(loc<11)
		{
			
		
		SPI_masterTransmit(number[loc]);
		//SPI_masterTransmit(number[loc++]);
		_delay_ms(1000);
		}
		loc=0;		
    }
}