/*
 * GccApplication2.c
 *
 * Created: 16-Jan-17 4:59:31 PM
 *  Author: Njj
 */ 

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>


/*

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
*/

volatile unsigned char value;
volatile char flag=0,flag1=0,flag2=0,overflag=0,deleteflag=0;
char com[20],com1[20],com2[20];
char start,start1,start2;
int i=0,j=0,k=0;
ISR(USART_RX_vect)
{
	
	
	
	value=UDR0;
	
	/*
	PORTB=0xff;
	_delay_ms(10);
	PORTB=0x00;
	
	*/
	if(start2==0)
	{
		
		if(value=='$')
		{
			
			start2=1;
			k=0;
			
		}
		
		
		
		
		
		
	}
	else 
	{
		
		if(value=='*')
		{
			
			start2=0;
			
			com2[k]='\0';
			flag2=1;
			k=0;
			//deleteflag=1;
			overflag=0;
		}
		
		
		
		
		else
		{
			
			com2[k++]=value;
		}
		
	}
	
	
	if(overflag==0)
	{
		
	
	 if(start==0)
	{
		
		if(value=='R')
		{
			com1[0]='R';
			start=1;
			 j=1;
			 
		}
		
		
		
		
		
		
	}		
	else
	{
		
		if(value=='G')
		{
			
			start=0;
			com1[j++]='G';
			com1[j]='\0';
			flag=1;
			j=0;
		}
		
		
		
		
		else
		{
			
			com1[j++]=value;
		}			
			
	}
	
	
	

	if(start1==0)
	{
		
		if(value=='C')
		{
			com[0]='C';
			start1=1;
			i=1;
		}
		
		
		
		
		
		
	}
	else
	{
		
		if(value=='\r')
		{
			
			start1=0;
			
			com[i]='\0';
			flag1=1;
			i=0;
		}
		
		
		
		
		else
		{
			
			com[i++]=value;
		}
		
	}
	
	
	}	
	
 
	
	

}


void send_char(volatile unsigned char c)
{
	
	UCSR0A=0x40;
	UDR0=c;
	while((UCSR0A & 0x40)==0);
}



void prints(char *ptr)
{
	
	while(*ptr)
	{
		
		send_char(*ptr);
		ptr++;
	}
}












int main(void)
{
	
	int len=0;
	DDRB=0xff;
	float a=0;
	char dispbuf[5];
	UBRR0H=0;
	UBRR0L=103;
	
	UCSR0A=0x80;
	UCSR0B=0x98;
	UCSR0C=0x06;
	sei();
	
	DDRB=0xff;
	/*DDRC=0xFF;
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
	
	
	
	lcd_command(0x80);
	lcd_print("njj");*/
	
	prints("AT\r\n");
	_delay_ms(2000);
	prints("ATE0\r\n");  //the code below is to send the message to any number
	_delay_ms(2000);
	//prints("ATD+918281967945;"); 
/*	prints("AT+CMGF=1\r\n");
	_delay_ms(2000);
	prints("AT+CMGS=\"+918281430041\"\r\n");
	_delay_ms(2000);
	prints("new message");
	
	_delay_ms(2000);
	send_char(0x1A);*/

prints("AT+CNMI=2,1,0,0,0\r\n");
	
	
	
	
	
	
    while(1)
    {
    
			if(flag==1)           //flag 1 loop is used to detect RING and to attend the call
			{
		//	lcd_command(0xc0);
			
		//	lcd_print(com1);
				if(strcmp(com1,"RING")==0)
		
				
				{
					
				
				/*PORTB|=0xf0;
				_delay_ms(100);
				PORTB&=~0xf0;
				_delay_ms(100);*/
				prints("ATA\r\n");
			
				
				}		
				
				flag = 0 ;		
						
			}
			
			
			if(flag1==1)
			{
				                  //flag used for blocking other loops while printing the message
				len=strlen(com);
			//	dtoa(len,dispbuf,2);
			//	lcd_command(0xc0);
				
			//	lcd_print(com);           //com contains the message location number in the sim
			//	lcd_command(0x85);
				
			//	lcd_print(dispbuf);        //these display functions are used to check the accuracy while programming
				len=len-1;
				
			//	lcd_command(0x89);
				
				
			//	lcd_data(com[len]);
				
				_delay_ms(3000);
				
				//to open the recieved specified message having location number as stored in 'com[len]'
				if(len==12)
				{
					
				
				prints("AT+CMGR=");
				send_char(com[len-1]);
				send_char(com[len]);
				prints("\r\n");
				}
				else
				{
					
					prints("AT+CMGR=");
					send_char(com[len]);
					prints("\r\n");
					
				}				
				
				
				if((strcmp(com,"CARRIER")))
				{
					
				//when call is recieved by gsm a msg'CARRIER'is sent back which sets the overflow flag unnecessarily to avoid tat if loop is used
				overflag=1;  
				}				
				flag1 = 0 ;
				
				
				
				
				
				
			
				
			}
			
			
			
			
			
			if(flag2==1)                     //com2 contains the message to be displayed
			{
				
				
			//	lcd_command(0x01);
				
			//	lcd_command(0x80);
				
			//	lcd_print(com2);
			//	prints(com2);
			
			
			prints("AT+CMGD=");        //for deleting the message that is once recieved
			send_char(com[len]);
			prints("\r\n");
			
			
	//	deleteflag=0;		
		flag2 = 0 ;
				
				
			}
			
			
	/*	if(deleteflag==0)
		{
			prints("AT+CMGD=");        //for deleting the message that is once recieved
			send_char(com[len]);
			prints("\r\n");
			
		}		
			*/	
			
			
			
				
    }
}