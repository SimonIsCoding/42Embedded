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

void uart_printstr(const char* str)
{
	while (*str)
	{
		uart_tx(*str);
		str++;
	}
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

void __vector_11(void) __attribute__((__signal__));

void __vector_11(void)
{
	static uint8_t count = 0;
	count++;
	if (count == 2)
	{
		uart_printstr("Hello World!\r\n");
		count = 0;
	}
}

//__vector11 - Timer/Counter1 Compare Match A
//p.66 - Interrupt Vectors in ATmega48A and ATmega48PA
//void __vector_11(void) __attribute__((__signal__));

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
	sei();	
	// F_CPU / Prescaler = Value for OCR1A
	// 16000000 / 256 = 62500;
	OCR1A = 62499; 
	// (p.142) - TCCR1B – Timer/Counter1 Control Register B
	TCCR1B |= (1 << WGM12) | (1 << CS12);
	//TCCR1A |= (1 << COM1A0);
	
	// 16.11.8 TIMSK1 – Timer/Counter1 Interrupt Mask Register (p.144)
	TIMSK1 |= (1 << OCIE1A);
	while (1)
	{
	}
}
