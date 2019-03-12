/*
 * IOlib.cpp
 *
 * Created: 08-03-2019 15:07:17
 *  Author: knn
 */ 

#include <avr/io.h>
#include "IOlib.h"


void setupLEDonPORTB(unsigned char n)  //sets PORTB.n to be an output
{
	DDRB |= (1<<n);
}
void setupBUTonPORTB(unsigned char n)  //sets PORTB.n to be an input Buuton connected to ground
{
	DDRB &= ~(1<<n);
	PORTD |= (1<<n);
}


bool getBUT(unsigned char n)  //  gets the immediate status of Button n....true for being pressed
{
	if (0 == (PINB & (1<<n)))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void setLED(unsigned char n, bool flag)  // sets the output value on pin PORTB.n. High if flag is true
{
	DDRB |= (1<<n); // PORTD pin1 is output for driving the LED
}
