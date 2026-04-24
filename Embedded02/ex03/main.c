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
	// p.201: 20.11.3 UCSRnB – USART Control and Status Register n B
	// Bit 7 – RXCIEn: RX Complete Interrupt Enable n
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

	/* Set frame format: 8data, 1stop bit - check p.203 
	check Table 20-11. UCSZn Bits Settings && Table 20-10. USBS Bit Settings */ 
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	//USBS0 &= ~(1 << TXB8);
}

char	invert_letter(char c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	else if (c >= 65 && c <= 90)
		c += 32;
	return c;
}

void __vector_18(void) __attribute__((__signal__));

void __vector_18(void)
{
	char c = UDR0;
	c = invert_letter(c);
	uart_tx(c);
}

int	main(void)
{
	USART_Init();
	sei();	
	// F_CPU / Prescaler = Value for OCR1A
	// 16000000 / 256 = 62500;
	OCR1A = 62499; 
	// (p.142) - TCCR1B – Timer/Counter1 Control Register B
	TCCR1B |= (1 << WGM12) | (1 << CS12);
	//TCCR1A |= (1 << COM1A0);
	
	while (1)
	{
	}
}
