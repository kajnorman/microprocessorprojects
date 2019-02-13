/*
 * ledflashlight.cpp
 Requirement 
		 The input pin is connected through a switch to ground
		 The output pin is connected to a power LED.
		 Each press of the button  shall cycle the lamp through a sequence of states being
			on
			half power
			blinking
			off
 Solution
		A samplerate of approximately 50 Hz is chosen  (20 ms) contactbounce should be minimized
		Trig made by the button will only occur 
			if (the "previous" buttonstate was not pressed and the current state is pressed)
		half-power will be simulated with a 25Hz 50% Duty cycle
		Blinking will be done with a frequency of 4 Hz (120 ms on  120 ms off)
		Version 1		
			20 msec is done by using a (blocking)  delay-function 

		
		
		
 *
 * Created: 11-02-2019 17:11:16
 * Author : knn
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#define BUTTON_PRESSED (0 == (PIND & (1<<PORTD2)))
#define LED_ON  PORTD |= 1<<PORTD1
#define LED_OFF  PORTD &= ~(1<<PORTD1)
#define FLASHOFF 0
#define FLASHON 1
#define FLASHDIM 2
#define FLASHBLINK 3




unsigned char FlashLightState = FLASHBLINK;
unsigned char CurrentButtonState=0,PreviousButtonState=0;




int main(void)
{
	DDRD |= (1<<DDD1); // PORTD pin1 is output for driving the power LED

	//If PORTxn is written logic one when the pin is configured as an input pin, the pull-up resistor is activated.
	DDRD &= ~(1<<DDD2);
	PORTD |= (1<<DDD2);
	
    while (1) 
    {
		PreviousButtonState = CurrentButtonState;
		CurrentButtonState = BUTTON_PRESSED;

		if((PreviousButtonState==0) && (CurrentButtonState!=0))
		{  //Change flashlight state
			if(FlashLightState==FLASHOFF)
			{
				 FlashLightState = FLASHBLINK;
			}
		else
			{
				FlashLightState = FLASHOFF;					
			}	
		}
		
		if(FlashLightState==FLASHBLINK)		
		{
			_delay_ms(100);
			LED_ON;
		}
		_delay_ms(100);
		LED_OFF;	
	}
}

