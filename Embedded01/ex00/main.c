#include <avr/io.h>

int	main(void)
{
	volatile long i = 0;// we use volatile to be able to enter in the useless while loop, otherwise it doesn't enter 
	// uint8_t is used because it has size of 1 byte. Which is the size of one operatio
	DDRB |= (1 << DDB0);

	// 255 * 255 * 128 ~= 8*10e6 operations
	// which represent 0.5 second for our microconrtoller
	// because we know it executes 16000000 operations in a second <=> F_CPU = 16000000UL
	// meaning 16 millions operation per second.
	// dans cette boucle while, il y a une vingtaine operations en Assembleur qui s'executent. Donc il faut diviser
	// 16e6 par 20 et ensuite par deux car on veut une demi seconde
	while (1)
	{
		i = 0;
		while (i < 400000)
			i++;
		PORTB ^= (1 << PORTB0);
	}
}
