

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



#define COL1() PORTA=0xf7
#define COL2() PORTA=0xfb
#define COL3() PORTA=0xfd
#define COL4() PORTA=0xfe
#define ROW1 0x80
#define ROW2 0x40
#define ROW3 0x20
#define ROW4 0x10


void lcd_command(char cmd)
{
	
	PORTB&=(~0x03);
	
	PORTC=cmd;
	PORTB|=0x04;
	PORTB&=(~0x04);
	PORTC=cmd<<4;
	PORTB|=0x04;
	PORTB&=(~0x04);
	_delay_ms(5);
	
}


void lcd_data(char data)
{
	
	PORTB|=0x01;
	PORTB&=(~0x02);
	
	PORTC=data;
	PORTB|=0x04;
	PORTB&=(~0x04);
	
	PORTC=data<<4;
	PORTB|=0x04;
	_delay_ms(5);
	PORTB&=(~0x04);
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

int main(void)
{
	DDRA=0x0f;
	PORTA|=0xf0;
	int a=1234;
	char dispbuf[5];
	DDRB=0x07;
	DDRC=0xFF;
	_delay_ms(5);
	PORTC = 0x30;
	
	_delay_ms(5);

	PORTC = 0x30;
	_delay_ms(5);
	lcd_command(0x30);
	_delay_ms(5);
	lcd_command(0x28);
	_delay_ms(5);

	lcd_command(0x01);
	lcd_command(0x06);
	lcd_command(0X0c);
	lcd_command(0x80);
	
	//functions:    lcd_print( ),   dtoa(xx,dispbuf,n)
	
	
	

	lcd_print("anoop and paul");
	//dtoa(a,dispbuf,4);
	//	lcd_print(dispbuf);
	int count=0;
	
	while(1)
	{
		
		  COL1();
		if((PINA & ROW1)==0){while((PINA & ROW1)==0);lcd_command(0xc0);lcd_data('a');count++;}
		if((PINA & ROW2)==0){while((PINA & ROW2)==0);lcd_command(0xc0);lcd_data('4');count++;}
		if((PINA & ROW3)==0){while((PINA & ROW3)==0);lcd_command(0xc0);lcd_data('7');count++;}
		if((PINA & ROW4)==0){while((PINA & ROW4)==0);lcd_command(0xc0);lcd_data('*');count++;}
		  COL2();
	    if((PINA & ROW1)==0){while((PINA & ROW1)==0);lcd_command(0xc0);lcd_data('1');count++;}
            if((PINA & ROW2)==0){while((PINA & ROW2)==0);lcd_command(0xc0);lcd_data('5');count++;}
	    if((PINA & ROW3)==0){while((PINA & ROW3)==0);lcd_command(0xc0);lcd_data('8');count++;}
            if((PINA & ROW4)==0){while((PINA & ROW4)==0);lcd_command(0xc0);lcd_data('0');count++;}
			COL3();
		if((PINA & ROW1)==0){while((PINA & ROW1)==0);lcd_command(0xc0);lcd_data('2');count++;}
	        if((PINA & ROW2)==0){while((PINA & ROW2)==0);lcd_command(0xc0);lcd_data('6');count++;}
		if((PINA & ROW3)==0){while((PINA & ROW3)==0);lcd_command(0xc0);lcd_data('9');count++;}
		if((PINA & ROW4)==0){while((PINA & ROW4)==0);lcd_command(0xc0);lcd_data('#');count++;}
			COL4();
		if((PINA & ROW1)==0){while((PINA & ROW1)==0);lcd_command(0xc0);lcd_data('3');count++;}
	        if((PINA & ROW2)==0){while((PINA & ROW2)==0);lcd_command(0xc0);lcd_data('b');count++;}
                if((PINA & ROW3)==0){while((PINA & ROW3)==0);lcd_command(0xc0);lcd_data('c');count++;}
		if((PINA & ROW4)==0){while((PINA & ROW4)==0);lcd_command(0xc0);lcd_data('d');count++;}
		
	       dtoa(count,dispbuf,3);		
               lcd_command(0xc6);
	       lcd_print(dispbuf);
		//_delay_ms(200);
	}
	
	
	
}