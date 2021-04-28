/*
 * IO.cpp
 *
 * Created: 24-10-2020 00:05:34
 *  Author: knn
 */ 

#include "IO.h"

PORTPin::PORTPin(PortnameType p, char pinr,bool direction)  //constructor takes portb-bit nr and direction as input
{
	Portname = p;   // to be followed up
	portnumber = pinr;
	if (Portname == B)
	{
		PORT = &PORTB;
		PIN = &PINB;
		DDR = &DDRB;
	}
	if (Portname == C)
	{
		PORT = &PORTC;
		PIN = &PINC;
		DDR = &DDRC;
	}
	if (Portname == D)
	{
		PORT = &PORTD;
		PIN = &PIND;
		DDR = &DDRD;
	}
	
	if(direction) *DDR |= (1<<portnumber);  //1 is output 0 is input
}

void PORTPin::digitalWrite(bool flag)  // sets the output value on pin to hi if flag is true
{
	if(flag)
	{
		*PORT |= (1<<portnumber); // PORTB.n set high
	}else
	{
		*PORT &= ~(1<<portnumber); // PORTB.n set high
	}
}

bool PORTPin::digitalRead()  //  gets the immediate status of Button n....true for being pressed
{
	if (0 == (*PIN & (1<<portnumber)))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Button::Wait_for_Press()
{   //  Blocking function call  !!
	while (digitalRead() == true)
	{
		//Do nothing
	}
}

bool Button::Pressed_since_last()
//returns true if the state of the button has changed from
//not being pressed
//to actively being pressed
//since last call of the same function
{
	bool currentstate_pressed, temp_ret;
	if  ((*PIN & (1<<portnumber)) == 0)
	currentstate_pressed = true;
	else
	currentstate_pressed = false;
	if ((last_state_pressed == false) && (currentstate_pressed	== true))
		temp_ret = true;
	else
		temp_ret = false;
	last_state_pressed=currentstate_pressed;
	return temp_ret;
}
