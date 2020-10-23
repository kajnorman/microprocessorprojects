/*
 * cpluslib2_infiles.cpp
 *
 * Created: 23-10-2020 23:57:34
 * Author : knn
 */ 


#include "IO.h"


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

