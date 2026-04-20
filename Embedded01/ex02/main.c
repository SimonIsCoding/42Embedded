// ref: ATmega48A/PA/88A/PA/168A/PA/328/P
// Microchip: megaAVR Data Sheet
#include <avr/io.h>

// what the subject ask us is to turn on the LED every 0.9second during 0.1second
// duty cycle: 
// Non inversed mode: ON-OFF
// inversed mode: OFF-ON
// the way the exercise was done was: first 0.1 seconds, the LED is ON, the other 0.9seconds, the LED is OFF
int	main(void)
{
	DDRB |= (1 << DDB1);
	// we are in Fast PWM mode
	// formula to calculate output frequency for Fast PWM (p.134)
	// fOCnxPWM = fclk_I/O / (N * 1 * TOP) 
	// (p.142) we know that TOP is ICR1 (mode 14)
	// TOP <=> ICR1 = 15624

	ICR1 = 15624;
	OCR1A = 1562;                            // max timer value
	// (1 << WGM13) | (1 << WGM12) | (1 << WGM11) to activate Fast PWM
	// (1 << CS12) | (1 << CS10); to configure the prescaler
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS10); // register to configure Timer1
	// (p.140): Table 16-2. Compare Output Mode, Fast PWM 
	// we want a non-inverted mode
	// |--ON (10%)--|------OFF (90%)------|
	// 0           1562                 15624
	TCCR1A |= (1 << COM1A1) | (1 << WGM11) ; // Automatic toggle for PB1 LED(p.140)

	while (1)
	{}
}
