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
#define LED_TOGGLE  PIND |= (1<<PIND1)
#define FLASHOFF 0
#define FLASHONFULL 1
#define FLASHONHALF 2
#define FLASHSLOWBLINK 3
#define FLASHFASTBLINK 4




unsigned char FlashLightState = FLASHFASTBLINK;
unsigned char CurrentButtonState=0,PreviousButtonState=0;
unsigned char delaycounter = 0;



int main(void)
{
	DDRD |= (1<<DDD1); // PORTD pin1 is output for driving the power LED

	//If PORTxn is written logic one when the pin is configured as an input pin, the pull-up resistor is activated.
	DDRD &= ~(1<<DDD2);
	PORTD |= (1<<DDD2);
	
    while (1) 
    {
	    	///////////////Handle the Button activation (going from not pressed to being pressed
		PreviousButtonState = CurrentButtonState;
		CurrentButtonState = BUTTON_PRESSED;

		if((PreviousButtonState==0) && (CurrentButtonState!=0))  
		{  //////////Change flashlight state based on the previous state
			if(FlashLightState==FLASHOFF)
				{
					 FlashLightState = FLASHONFULL;
				}
			else
				if(FlashLightState==FLASHONFULL)
						{
							FlashLightState = FLASHONHALF;
						}
					else
						if(FlashLightState==FLASHONHALF)
							{
								FlashLightState = FLASHSLOWBLINK;
							}
						else
							if(FlashLightState==FLASHSLOWBLINK)
								{
									FlashLightState = FLASHFASTBLINK;
								}
							else
								if(FlashLightState==FLASHFASTBLINK)
									{
										FlashLightState = FLASHOFF;
									}
		}
		
	    
	    
	    
	    
	    
	    ////////////////Handling the output based on the state.
		if(FlashLightState==FLASHONFULL)
		{
			LED_ON;
		}

		if(FlashLightState==FLASHONHALF)
		{
			LED_TOGGLE;
		}

		if(FlashLightState==FLASHOFF)
		{
			LED_OFF;
		}

		if(FlashLightState==FLASHSLOWBLINK)
		{
			if (delaycounter >= 20)
			{
				LED_TOGGLE;
				delaycounter=0;
			}
		}

		if(FlashLightState==FLASHFASTBLINK)
		{
			if (delaycounter >= 3)
			{
				LED_TOGGLE;
				delaycounter=0;
			}
		}

		_delay_ms(20);
		delaycounter++;
	}
}

