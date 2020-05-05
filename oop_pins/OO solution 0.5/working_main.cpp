/* * test_of_h_and_c_files.cpp
 * * Created: 08-03-2019 13:23:28
 
 Version  0.5
 
The purpose with this task is to make a library that does 
		some of the Arduino-like handling of io-pins
		starting with one port only PORTB
		using the concept of
				Buttons for input
					set up as input 
					automatically use pull up
					button connects to ground
					automatically invert the signal 
							so when the button is activated or	pressed
							I get a '1' on the when requesting through the library
				LED for input 
					set up as output

Example :
	#include  "iolib.h"
		
	int main(void)
	{
	
		BUTonPORTB button = BUTonPORTB(0);  //sets PORTB.0 to be an input Buuton connected to ground
		LEDonPORTB redled = LEDonPORTB(1);  //sets PORTB.1 to be an output


		while(1)
		{
			bool flag;  //The LED will light while the button is being pressed
			flag = button.pressed();
			redled.activate(flag);
			// or redled.activate(button.pressed());
		}
	}

 * Author : knn
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL  // 1 MHz
#include <util/delay.h>

class LEDonPORTB
{
public:
LEDonPORTB(unsigned char n);  //constructor takes portb-bit nr as input
void activate(bool flag);  // sets the output value on pin to hi if flag is true
void toggle();
private:
unsigned char portnumber;
};

LEDonPORTB::LEDonPORTB(unsigned char n)  //constructor takes portb-bit nr as input
{
	DDRB |= (1<<n);
	portnumber = n;
}

void LEDonPORTB::activate(bool flag)  // sets the output value on pin to hi if flag is true
{
	if (flag)
		PORTB |= (1<<portnumber); // PORTB.n set high
	else
		PORTB &=  ~(1<<portnumber); // PORTB.n set high
		
}

void LEDonPORTB::toggle()
{
	if (0 == (PORTB & (1<<portnumber))) //led is off
	{
		PORTB |= (1<<portnumber); // turn it on
	}
	else
	{
		PORTB &=  ~(1<<portnumber); //turn it off
	}
}


class BUTonPORTB
{
public:
BUTonPORTB(unsigned char n);  //sets PORTB.n to be an input Buuton connected to ground
bool pressed();  //  gets the immediate status of Button n....true for being pressed
void waitforpress();
void waitforrelease();
private:
unsigned char portnumber;
};



BUTonPORTB::BUTonPORTB(unsigned char n)  //sets PORTB.n to be an input Buuton connected to ground
{
	DDRB &= ~(1<<n);  //input
	PORTB |= (1<<n);  //pull up
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

void BUTonPORTB::waitforpress()
{
	while ( ! pressed())
	{
		_delay_ms(10);
	}
	
}

void BUTonPORTB::waitforrelease()
{
	while (pressed())
	{
		_delay_ms(10);
	}
	
}

		
int main(void)
{
	
	BUTonPORTB button = BUTonPORTB(0);  //sets PORTB.0 to be an input Buuton connected to ground
	LEDonPORTB redled = LEDonPORTB(1);  //sets PORTB.1 to be an output


	while(1)
	{
        button.waitforpress();
		redled.toggle();
        button.waitforrelease();
	}
}





