
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
	
	while(*ptr !='\0')
	{
		
		send_char(*ptr);
		ptr++;
	}
}

void TWIint()
{
	
	TWSR=0x00;
	TWBR=18;
	TWCR=0x04;
	
}

void TWIstart()
{
	
	TWCR=0xA4;
	
	while((TWCR & 0x80)==0);
	
}

void TWIstop()
{
	
	TWCR=0x94;
}


void TWIwrite(char dat)
{
	
	TWDR=dat;
	TWCR=0x84;
	while((TWCR & 0x80)==0);
	
	
}

char TWIreadack()
{
	TWCR=0xC4;
	while((TWCR & 0x80)==0);
	return TWDR;
	
}

char TWIreadnack()
{
	TWCR=0x84;
	while((TWCR & 0x80)==0);
	return TWDR;
	
}


void EEwritebyte(char loc,char data)
{
	
	_delay_ms(10);
	TWIstart();
	
	
	TWIwrite(0xA0);
	
	TWIwrite(loc);
	
	TWIwrite(data);
	
	TWIstop();
	
}


void EEwriteword(char loc,char *data)
{
	
	_delay_ms(10);
	TWIstart();
	
	
	TWIwrite(0xA0);
	
	TWIwrite(loc);
	while((*data) !='\0')
	{
		_delay_ms(10);
		TWIwrite(*(data++));
	}	
	TWIwrite('\0');
	TWIstop();
	
}


char EEreadbyte(char loc)
{
	
	char edat=0;
	_delay_ms(10);
	TWIstart();
	TWIwrite(0xA0);
	TWIwrite(loc);
	TWIstart();
	TWIwrite(0xA1);
	edat=TWIreadnack();
	
	
	TWIstop();
	
	return edat;
}


void EEreadword(char loc,char *ch,int size)
{
	int i;
	
	
	_delay_ms(10);
	TWIstart();
	TWIwrite(0xA0);
	TWIwrite(loc);
	TWIstart();
	TWIwrite(0xA1);
	for(i=0;i<size;i++)
	{
		ch[i]=TWIreadack();
	}	
	ch[i]='\0';
	
	
	TWIstop();
	
}

int main(void)
{
	char dat[20];
	char datt;
	
	UBRRH=0;
	UBRRL=103;
	
	
	UCSRA=0x00;
	UCSRB=0x98;
	UCSRC=0x86;
	sei();
	
	
	
	TWIint();

/*	EEwritebyte(81,'y');
	EEwritebyte(82,'z');
        datt=EEreadbyte(81);
	send_char(datt);*/
	
	
	//EEwriteword(27,"ni k");
	
	EEreadword(27,dat,4);
	
	prints(dat);
	
	
	
	while(1);
	
}