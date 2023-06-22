

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

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

	lcd_print("nikhil joseph jo");
	//dtoa(a,dispbuf,4);
	//	lcd_print(dispbuf);
	
	
	
	
	
}