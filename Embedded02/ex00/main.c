// ref: ATmega48A/PA/88A/PA/168A/PA/328/P
// Microchip: megaAVR Data Sheet

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//the subject specifies: The MCU’s UART must be configured as 115200 8N1
//meaning: Baudrate: 115200 8bits 1 stop

//UBRRnL must be calculated based on UART_BAUDRATE and F_CPU
//UBRR = 16 = 0000 0000 0001 0000
//UART_BAUDRATE = 115200 - what about 8N1 - BaudRate -> bit per second bps
//F_CPU			= 16000000UL

//to build this function, check 20.6.1 Sending Frames with 5 to 8 Data Bit - p.186
void	uart_tx(char c)
{
	while ( !( UCSR0A & (1 << UDRE0)) )
		;
/* Put data into buffer, sends the data */
	UDR0 = c;
}

void USART_Init()
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(16 >> 8);
	UBRR0L = (unsigned char)(16);

	//activate double speed - Clock Generation p.180 
	UCSR0A |= (1 << U2X0);

	/* able receiver and transmitter - as mentionned in the datasheet piece of code */
	// p.185: USART Initialization
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	/* Set frame format: 8data, 1stop bit - check p.203 
	check Table 20-11. UCSZn Bits Settings && Table 20-10. USBS Bit Settings */ 
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	//USBS0 &= ~(1 << TXB8);
}

// to caclulate UBRRn, we need to check p.180 of the datasheet:
// we have two formulas for Asynchronous modes
// we have to check p.199 of the datasheet for F_CPU = 16e6, which one is the best
// We can see that the error rate is lower for U2Xn = 1, so we will use the U2X0 = 1 formula,
// meaning the double speed one:
// UBRRn = (fOSC / (8 * BAUD)) - 1
// fOSC = 16 000 000, BAUD = 115200
// UBRRn = 16.3611111 ~= 16

int	main(void)
{
	USART_Init();

	while (1)
	{
		uart_tx('Z');
		_delay_ms(1000);
	}
}
