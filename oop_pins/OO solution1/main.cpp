/*
 * OO solution1.cpp
 *
 * Created: 08-03-2019 15:23:25

 
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
		 
 * Author : knn
 */ 

#include <avr/io.h>
#include "IOlib.h"

		
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

