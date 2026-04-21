// ref: ATmega48A/PA/88A/PA/168A/PA/328/P
// Microchip: megaAVR Data Sheet

#include <avr/io.h>

// I am using the 1024 Prescaler, but I could have used a more accurate one like 256
// WHy ?
// Because Timer1 is a 2bytes/octet register
// 2 bytes meaning the counter max value can reach 65535
// and : F_CPU: 16 000 000 / 256 = 62500, meaning in the range between 0 < 62500 < 65535
// and instead of using the datasheet complex formula (p.156), I could have use:
// 16 000 000 / 1024 = 15 625 -> intern clock in for 1Hz
// And we want the light blinking every 0.5 seconds -> 15 625 * 0.5 = 7812.5 => rounded = 7812

int	main(void)
{
	//configure PB1 LED as output in DDRB register, by default it is in input
	// in output because we want to show the light
	DDRB |= (1 << DDB1);
	
	// Refering to the ATMega328p Datasheet:
	// fOCnx = fclk_I/O / (2 * N * (1 + OCRnx)) (p.156)
	// knowing: FOCnx = 1Hz, fclk_I/O = 16*10e6, N = 1024
	// OCRnx = 7812;
	// OCR1A because we refer to Timer1 (p. 121)
	OCR1A = 7812;                            // max timer value
	// CTC Mode  (p.155)
	// Activate WGM12 (p.146) to reinitialise CTC when OCR1A is reached
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);	// register to configure Timer1
	TCCR1A |= (1 << COM1A0); // Automatic toggle for PB1 LED(p.140)
	while(1)
	{
	}
}
