
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
//header to enable data flow control over pins
#define F_CPU 8000000UL
//telling controller crystal frequency attached
//header to enable delay function in program
int UBBRValue = 6;//AS described before setting baud rate (9600)
void main(void)
{
	DDRD =0b11111110;// 1 << PIND1;//pin1 of portD as OUTPUT
	DDRA =0b00000000;// ~(1 << PIND0);//pin0 of portD as INPUT
	PORTC=0b11111111;// 1 << PIND0;
	PORTC=0;
	
	
	//Put the upper part of the baud number here (bits 8 to 11)
	UBRRH = (unsigned char) (UBBRValue >> 8);
	
	//Put the remaining part of the baud number here
	UBRRL = (unsigned char) UBBRValue;
	
	//Enable the receiver and transmitter
	UCSRB = (1 << RXEN) | (1 << TXEN);
	
	//Set 2 stop bits and data bit length is 8-bit
	UCSRC = (1 << USBS) | (3 << UCSZ0);
	
	while (1)
	{			
			while (! (UCSRA & (1 << UDRE)) );
			{
				UDR = 0b11110001;//once transmitter is ready sent eight bit data
			}
	}
}
