/*
 * timer0_external_input.cpp
 *
 * Created: 19-02-2019 10:05:57
 * Author : knn
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)  //
{
	DDRB = 0xff;
	// PD4 is input to TIMER0
	
	DDRD &= ~(1<<PORTD4);
	PORTD |= (1<<PORTD4);
	
	
	TCCR0B |= (1<<CS02)|(1<<CS01)|(1<<CS00);
	
	
	while (1)
	{
		PORTB=TCNT0;   
	}
}

