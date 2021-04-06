#include <avr/io.h>
#include <stdbool.h>

void setupLEDonPORTB(unsigned char n)  //sets PORTB.n to be an output
{
	DDRB |= (1<<n);		
}

void setupBUTonPORTB(unsigned char n)  //sets PORTB.n to be an input Button connected to ground
{
	DDRB &= ~(1<<n);
	PORTB |= (1<<n);
}

unsigned char getBUT(unsigned char n)  //  gets the immediate status of Button n....true for being pressed
{
	if (0 == (PINB & (1<<n)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void setLED(unsigned char n, unsigned char flag)  // sets the output value on pin PORTB.n. High if flag is true
{
	if (flag)
	PORTB |= (1<<n); // PORTD pin1 is output for driving the LED
	else
	PORTB &= ~(1<<n); // PORTD pin1 is output for driving the LED
}

int main(void)
{
	setupLEDonPORTB(0);  //sets PORTB.0 to be an output
	setupBUTonPORTB(1);  //sets PORTB.1 to be an input Button connected to ground

	while(1)
	{
		unsigned char flag;  //The LED will light while the button is being pressed
		flag = getBUT(1);
		setLED(0,flag);
	}
}
