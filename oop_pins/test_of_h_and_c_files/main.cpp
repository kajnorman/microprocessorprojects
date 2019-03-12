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
		
		setupLEDonPORTB(0);  //sets PORTB.0 to be an output 
		setupBUTonPORTB(1);  //sets PORTB.1 to be an input Buuton connected to ground
		
		int main(void)
		{
			while(1)
			{
				bool flag;  //The LED will light while the button is being pressed
				flag = getBUT(1);
				setLED(0,flag);
			}
		}
		
					
 
 * Author : knn
 */ 

#include <avr/io.h>
#include "IOlib.h"





		
int main(void)
{
	setupLEDonPORTB(0);  //sets PORTB.0 to be an output
	setupBUTonPORTB(1);  //sets PORTB.1 to be an input Buuton connected to ground


	while(1)
	{
		bool flag;  //The LED will light while the button is being pressed
		flag = getBUT(1);
		setLED(0,flag);
	}
}

