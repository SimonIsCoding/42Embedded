#include <avr/io.h>

/* 
 * DDRB0: The D0 LED
 * PORTB0: The intensity in Volt. 1 = 5V, 0 = 0V
 initially, we have:
	DDRB = 0b00000000;
	PORTB = 0b00000000;
 * DDRB |= (1 << DDB0) => We shift the bit to turn on the DDB0 LED
 * We add 5V to PORTB to make the light brigths
 * it became:
	DDRB = 0b00000001;
	PORTB = 0b00000001;
*/

int	main(void)
{
	DDRB |= (1 << DDB0);
	PORTB |= (1 << PORTB0);
	while (1)
	{
	}
	return (0);
}
