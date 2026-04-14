#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD &= ~(1 << DDD2);
	PORTD |= (1 << PD2);
	while (1)
	{

		if (!(PIND & (1 << PD2)))
		{
			DDRB |= (1 << DDB0);
			PORTB |= (1 << PORTB0);
		}
		else
		{
			DDRB &= (0 << DDB0);
			PORTB &= (0 << PORTB);
		}
	}
	return (0);
}
