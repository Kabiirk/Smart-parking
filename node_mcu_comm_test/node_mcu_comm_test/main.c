/*
 * node_mcu_comm_test.c
 *
 * Created: 10/20/2019 3:27:02 PM
 * Author : kabii
 */ 

//#define F_CPU 16000000UL
#define F_CPU 16000000UL     // define cpu frquency
#include<avr/io.h>
#include<util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)     // convert to baudrate dec value

void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);         // Turn on transmission and reception by setting RX Tx bits
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);    // Use 8-bit character sizes
	UBRRL = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value
	UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value
}

void UART_TxChar(char c)
{
	while (! (UCSRA & (1<<UDRE))); // Wait for empty transmit buffer
	UDR = c;
}

void UART_sendString(char *str)
{
	unsigned char s=0;
	
	while (str[s]!=0) // string till null
	{
		UART_TxChar(str[s]);    // send s to UART_TxChar(s) function
		s++;
	}
}

int main(void)
{
	
	UART_init(9600);    // initialize UART communication
	
	UART_sendString("TEST");
	//DDR Data Direction Register
	DDRA |= (1<<0); //Setting pin0 of PORTA for output mode  -led
	DDRA &= ~(1<<1); //Setting pin1 of PORTA for input mode -push button
	PORTA |= (1<<1); //Giving a high value to pin 1
	
	while(1)
	{
			UART_sendString("SEND");      // send string
	}
}