/*
 * IOlib.cpp
 *
 * Created: 08-03-2019 15:07:17
 *  Author: knn
 */ 

#include <avr/io.h>
#include "IOlib.h"

OUTonPORTB::OUTonPORTB(unsigned char n)  //constructor takes portb-bit nr as input
{
	DDRB |= (1<<n);
	portnumber = n;
}

void OUTonPORTB::activate(bool flag)  // sets the output value on pin to hi if flag is true
{
	PORTB |= (1<<portnumber); // PORTB.n set high
}

BUTonPORTB::BUTonPORTB(unsigned char n)  //sets PORTB.n to be an input Buuton connected to ground
{
	DDRB &= ~(1<<n);  //input
	PORTD |= (1<<n);  //pull up
	portnumber = n;   //save the number
}

bool BUTonPORTB::pressed()  //  gets the immediate status of Button n....true for being pressed
{
	if (0 == (PINB & (1<<portnumber)))
	{
		return true;
	}
	else
	{
		return false;
	}
}
