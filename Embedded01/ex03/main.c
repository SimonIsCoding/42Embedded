// ref: ATmega48A/PA/88A/PA/168A/PA/328/P
// Microchip: megaAVR Data Sheet

#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB |= (1 << DDB1);
	DDRD &= ~(1 << PD2);
	DDRD &= ~(1 << PD4);

	ICR1 = 15624;
	OCR1A = 1562;                            // max timer value
	// (1 << WGM13) | (1 << WGM12) | (1 << WGM11) to activate Fast PWM
	// (1 << CS12) | (1 << CS10); to configure the prescaler
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10); // register to configure Timer1
	// (p.141): Table 16-3. Compare Output Mode, Phase Correct and Phase and Frequency Correct PWM 
	TCCR1A |= (1 << COM1A1) | (1 << WGM11); // Automatic toggle for PB1 LED(p.140)

	while (1)
	{
		//	si SW1 appuyé  → OCR1A += 10% de ICR1
		if (!(PIND & (1 << PD2)))
		{
			if (OCR1A < 15620)
				OCR1A += 1562;
			while(!(PIND & (1 << PD2)))	
				;
			_delay_ms(20);
		}
		//  si SW2 appuyé  → OCR1A -= 10% de ICR1
		if (!(PIND & (1 << PD4)))
		{
			if (OCR1A > 1562)
				OCR1A -= 1562;
			while(!(PIND & (1 << PD4)))
				;
			_delay_ms(20);
		}
	}
}
