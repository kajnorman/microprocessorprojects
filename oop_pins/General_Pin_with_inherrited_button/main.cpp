/* * test_of_h_and_c_files.cpp
 * * Created: 08-10-2020 13:23:28
 
 Version  0.7
 
The purpose with this task is to make a library that does 
		some of the Arduino-like handling of io-pins(but OO) 
			digitalRead()
			digitalWrite()
			PORTPin()  //constructor
		a button derived from the portpin
			Pressed_since_last();
			Wait_for_Press();			

Example :

		Button startbutton = Button(D,7,0);  //sets PORTD.7 to be an input (last argument 1 for out 0 for in)
		PORTPin statusled = PORTPin(D,6,1);  //sets PORTD.6 to be an output (last argument 1 for out 0 for in)
		startbutton.digitalWrite(1); //writing 1 to an input allows setting the pullup
		
		Button togglebutton = Button(B,0,0);  //sets PORTB.0 to be an input (last argument 1 for out 0 for in)
		PORTPin redled = PORTPin(B,1,1);  //sets PORTB.1 to be an output (last argument 1 for out 0 for in)
		togglebutton.digitalWrite(1); //writing 1 to an input allows setting the pullup

		startbutton.Wait_for_Press();  //blocking untill pressed
		statusled.digitalWrite(true);

		while(1)
		{
			if (togglebutton.Pressed_since_last())
			{
				redled.digitalWrite(! redled.digitalRead());
			}
			_delay_ms(10);
		}

 * Author : knn
 */ 

#include <avr/io.h>
#include <stdbool.h>
#define F_CPU 8000000
#include "util/delay.h"



typedef enum
{
	B,
	C,
	D
}   PortnameType;


class PORTPin
{
public:
PORTPin(PortnameType p, char pinr,bool direction);  //constructor takes portb-bit nr and direction as input
void digitalWrite(bool flag);  // sets the output value on pin to hi if flag is true
bool digitalRead(void);  // sets the output value on pin to hi if flag is true
protected:
volatile uint8_t	*PORT;// pointer to PORT
volatile uint8_t	*PIN;// pointer to PIN
volatile uint8_t	*DDR;// pointer to DDR
unsigned char portnumber;
PortnameType Portname;
};



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
	
	if(direction) *DDR = (1<<portnumber);  //1 is output 0 is input
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




class Button : public PORTPin
{
bool last_state_pressed = false;	
public:
Button(PortnameType p, char pinr,bool direction) :  PORTPin(p,pinr,direction){}
//The button constructor only runs its "parent"

bool Pressed_since_last();
void Wait_for_Press();

};


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


int main(void)
{
	Button startbutton = Button(D,7,0);  //sets PORTD.7 to be an input (last argument 1 for out 0 for in)
	PORTPin statusled = PORTPin(D,6,1);  //sets PORTD.6 to be an output (last argument 1 for out 0 for in)
	startbutton.digitalWrite(1); //writing 1 to an input allows setting the pullup
				
	Button togglebutton = Button(B,0,0);  //sets PORTB.0 to be an input (last argument 1 for out 0 for in)
	PORTPin redled = PORTPin(B,1,1);  //sets PORTB.1 to be an output (last argument 1 for out 0 for in)
	togglebutton.digitalWrite(1); //writing 1 to an input allows setting the pullup

	startbutton.Wait_for_Press();  //blocking untill pressed
	statusled.digitalWrite(true);

	while(1)
	{
		if (togglebutton.Pressed_since_last())
		{
			redled.digitalWrite(! redled.digitalRead());
		}
		_delay_ms(10);
	}
}





