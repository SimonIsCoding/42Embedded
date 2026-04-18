int	main(void)
{
	//on veut turn off et turn on LA LED D2 PB1
	//on doit configurer le timer1 pour controler la led
	//on doit ecrire une while(1) vide
	//Et on ne peut pas utiliser PORTX
	
	volatile long i = 0;
	DDRB |= (1 << DDB1);

	TCCR1B |= (1 << CS12) | (1 << CS10);

	while(1)
	{
	}
}
