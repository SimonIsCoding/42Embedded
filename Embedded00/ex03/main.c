#include <avr/io.h>
#include <util/delay.h>

int	main(void)
{
	DDRB |= (1 << DDB0);
	DDRD &= ~(1 << DDD2);
	while (1)
	{
		if (!(PIND & (1 << PD2)))
		{
			PORTB ^= (1 << PORTB0);	
			_delay_ms(200);
			while(!(PIND & (1 << PD2)))
				;
		}
	}
	return (0);
}
