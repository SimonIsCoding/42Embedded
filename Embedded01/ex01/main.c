// ref: ATmega48A/PA/88A/PA/168A/PA/328/P
// Microchip: megaAVR Data Sheet

#include <avr/io.h>

int	main(void)
{
	//on veut turn off et turn on LA LED D2 PB1
	//on doit configurer le timer1 pour controler la led
	//on doit ecrire une while(1) vide
	//Et on ne peut pas utiliser PORTX
	
	//configurer la led PB1 en sortie dans le registre DDRB
	DDRB |= (1 << DDB1);
	
	// Refering to the ATMega328p Datasheet:
	// fOCnx = fclk_I/O / (2 * N * (1 + OCRnx)) (p.156)
	// knowing: FOCnx = 1Hz, fclk_I/O = 16*10e6, N = 1024
	// OCRnx = 7812;
	// OCR1A because we refer to Timer1 (p. 121)
	OCR1A = 7812;                            // max timer value
	// CTC Mode  (p.155)
	// Activate WGM12 p.146 to reinitialise CTC when OCR1A is reached
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);	// register to configure Timer1
	TCCR1A |= (1 << COM1A0); // Automatic toggle for PB1 LED(p.140)
	while(1)
	{
	}
}
