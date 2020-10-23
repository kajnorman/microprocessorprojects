/*
 * IO.h
 *
 * Created: 23-10-2020 23:59:40
 *  Author: knn
 */ 

#ifndef IO_H_
#define IO_H_

#include <avr/io.h>
#include <stdbool.h>
#define F_CPU 8000000
#include "util/delay.h"

typedef enum
{	B,	C,	D}
PortnameType;

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

class Button : public PORTPin
{
	bool last_state_pressed = false;
	public:
	Button(PortnameType p, char pinr,bool direction) :  PORTPin(p,pinr,direction){}
	//The button constructor only runs its "parent"
	bool Pressed_since_last();
	void Wait_for_Press();
};
#endif /* IO_H_ */
