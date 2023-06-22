

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void lcd_command(char cmd)
{
	
	PORTB&=(~0x01);
	PORTC=cmd;
	PORTB|=0x02;
	_delay_ms(5);
	PORTB&=(~0x02);
	_delay_ms(5);
}


void lcd_data(char data)
{
	
	PORTB|=0x01;
	PORTC=data;
	PORTB|=0x02;
	_delay_ms(5);
	PORTB&=(~0x02);
	_delay_ms(5);
}

void lcd_print(char *ptr)
{
	
	while(*ptr!=0)
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
	DDRB=0x03;
	DDRC=0xFF;
	DDRD=0x01;
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
	
	while(1)
	{
		
		
		a=4.88*read_adc(0);

		
		dtoa(a,dispbuf,4);
		lcd_command(0x80);
		lcd_print(dispbuf);
		lcd_command(0x85);
		lcd_print("mV");
		
		
		



		




	}
	
	
}