/*
 * adv_micro_proj_atmega32.c
 *
 * Created: 10/16/2019 11:27:57 PM
 * Author : kabii
 */ 

#ifndef F_CPU
#define F_CPU (1000000UL) // 1 MHz clock speed
#endif
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	//UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UCSRC |= (1 << USBS) | (1 << UCSZ0);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

 void UART_TxChar(char c)
 {
	 while (! (UCSRA & (1<<UDRE)));
	 UDR = c;
 }
 
 void UART_sendString(char *str)
 {
	 unsigned char s=0;

	 while (str[s]!=0)
	 {
		 UART_TxChar(str[s]);
		 s++;
	 }
 }

int main(void)
{
	DDRA = 0x00; //PORTA as i/p
	DDRC = 0xFF; //PORTC as o/p
	//String slot1[12] = "a";
	//char slot2[12] = "b";
	//char final[24];
	
	while(1)
	{
		if (PINA & 0b00000001)
		{
			PORTC = PORTC | 0b00000001;
			//slot1[20] = "Full1";
		}
		else
		{
			PORTC = 0x00;
			//slot1[20] = "Empty1";
		}
		
		if (PINA & 0b00000010)
		{
		
			PORTC = PORTC | 0b00000010;
			//slot2[20] = "Full2";	
		}

		else
		{
			PORTC =0x00;
			//slot2[20] = "Empty2";
			
		}
	}
	return 0;
	
	//final = char *strcat(slot1,slot2);
	//UART_init(9600);
	//UART_sendString(final);
}