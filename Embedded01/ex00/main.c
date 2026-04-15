#include <avr/io.h>

int	main(void)
{
	volatile long i = 0;
	// uint8_t is used because it has size of 1 byte. Which is the size of one operation
	DDRB |= (1 << DDB0);

	// 255 * 255 * 128 ~= 8*10e6 operations
	// which represent 0.5 second for our microconrtoller
	// because we know it executes 16000000 operations in a second <=> F_CPU = 16000000UL
	// meaning 16 millions operation per second.
	while (1)
	{
		i = 0;
		while (i < 400000)
			i++;
		PORTB ^= (1 << PORTB0);
	}
}
