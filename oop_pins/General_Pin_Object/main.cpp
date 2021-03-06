/* * test_of_h_and_c_files.cpp
 * * Created: 08-10-2020 13:23:28
 
 Version  0.7
 
The purpose with this task is to make a library that does 
		some of the Arduino-like handling of io-pins

Example :
		
	int main(void)
	{
	
		PORTPin button = PORTPin(B,0,0);  //sets PORTB.0 to be an input (last argument 1 for out 0 for in)
		PORTPin redled = PORTPin(B,1,1);  //sets PORTB.1 to be an output (last argument 1 for out 0 for in)
		button.digitalWrite(1); //writing 1 to an input allows setting the pullup

		while(1)
		{
			bool flag;  //The LED will light while the button is being pressed
			flag = button.digitalRead();
			redled.digitalWrite(flag);
			// or redled.digitaWrite(button.digitalRead());
		}
	}

 * Author : knn
 */ 

#include <avr/io.h>
#include <stdbool.h>



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
private:
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


int main(void)
{
		
	PORTPin button = PORTPin(B,0,0);  //sets PORTB.0 to be an input (last argument 1 for out 0 for in)
	PORTPin redled = PORTPin(B,1,1);  //sets PORTB.1 to be an output (last argument 1 for out 0 for in)
	button.digitalWrite(1); //writing 1 to an input allows setting the pullup

	while(1)
	{
		bool flag;  //The LED will light while the button is being pressed
		flag = button.digitalRead();
		redled.digitalWrite(flag);
		// or redled.digitaWrite(button.digitalRead());
	}
}





