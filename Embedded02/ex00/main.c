// ref: ATmega48A/PA/88A/PA/168A/PA/328/P
// Microchip: megaAVR Data Sheet

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define FOSC	1843200 // Clock Speed
#define BAUD	115200
#define MYUBRR	FOSC/16/BAUD-1

//115200 8N1
//UBRRnL must be calculated based on UART_BAUDRATE and F_CPU
//UART_BAUDRATE = 115200 - what about 8N1 - BaudRate -> bit per second bps
//F_CPU			= 16000000UL

void	uart_init()
{
}

void	uart_tx(char c)
{
}

void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

int	main(void)
{
	USART_Init(MYUBRR);

	/* able receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	while (1)
	{
	}
}
