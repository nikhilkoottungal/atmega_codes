

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

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


void RTCwritebyte(char loc,char data)
{
	
	_delay_ms(10);
	
	TWIstart();
	TWIwrite(0xD0);
	TWIwrite(loc);
	TWIwrite(data);
	
	TWIstop();

	
}


char RTCreadbyte(char loc)
{
	
	char edat=0;
	
	_delay_ms(10);
	
	TWIstart();
	TWIwrite(0xD0);
	TWIwrite(loc);
	TWIstart();
	TWIwrite(0xD1);
	edat=TWIreadnack();
	
	TWIstop();
	
	return edat;
}




void lcd_command(char cmd)
{
	
	PORTB&=(~0x01);
	PORTD=cmd;
	PORTB|=0x02;
	_delay_ms(5);
	PORTB&=(~0x02);
	_delay_ms(5);
}


void lcd_data(char data)
{
	
	PORTB|=0x01;
	PORTD=data;
	PORTB|=0x02;
	_delay_ms(5);
	PORTB&=(~0x02);
	_delay_ms(5);
}

void lcd_print(char *ptr)
{
	
	while(*ptr!='\0')
	{
		
		lcd_data(*ptr);
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

int main(void)
{
	
	
	char dat=0;
	char sec,min,hour;
	
	
	/*UBRRL=103;
	UBRRH=0;
	UCSRA=0x00;
	UCSRB=0x98;
	UCSRC=0x86;*/
//	sei();

	TWIint();
	
	int a=1234;
	char dispbuf[5];
	DDRB=0x03;
	DDRD=0xFF;
	_delay_ms(5);
	lcd_command(0x30);
	_delay_ms(5);
	lcd_command(0x30);
	_delay_ms(5);
	lcd_command(0x30);
	_delay_ms(5);
	lcd_command(0x38);
	_delay_ms(5);
	lcd_command(0x01);
	lcd_command(0x06);
	lcd_command(0X0C);
	lcd_command(0x80);
	
	//functions:    lcd_print( ),   dtoa(xx,dispbuf,n)
	
	
	//lcd_data('n');

	//lcd_print("nikhil joseph jo");
	//dtoa(a,dispbuf,4);
	//	lcd_print(dispbuf);
	
	
	RTCwritebyte(0,0x50);
	RTCwritebyte(1,0x36);
	RTCwritebyte(2,0x21);
	
	
	while(1)
	{
		
		 sec=RTCreadbyte(0);
		 min=RTCreadbyte(1);
		 hour=RTCreadbyte(2);
		 
		 lcd_command(0x01);
		 lcd_command(0x80);
		 
		 lcd_data(((hour>>4) & 0x03)+'0');
		 lcd_data(((hour) & 0x0f)+'0');
		 lcd_data(':');
		 
		 lcd_data(((min>>4) & 0x0f)+'0');
		 lcd_data(((min) & 0x0f)+'0');          //time in ascii format for lcd
		 lcd_data(':');
		 
		 lcd_data(((sec>>4) & 0x0f)+'0');
		 lcd_data(((sec) & 0x0f)+'0');
		 _delay_ms(1000);
	}
	
	
	
	
	
}