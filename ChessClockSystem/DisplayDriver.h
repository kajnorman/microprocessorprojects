/* 
* DisplayDriver.h
*
* Created: 19-10-2019 22:02:20
* Author: knn
*/


#ifndef __DISPLAYDRIVER_H__
#define __DISPLAYDRIVER_H__

#include<avr/io.h>

#define STB  0
#define STBLO  (PORTB &= ~(1<<0))
#define STBHI  (PORTB |= (1<<0))
#define CLK	 1
#define CLKLO  (PORTB &= ~(1<<1))
#define CLKHI  (PORTB |= (1<<1))
#define DIO	 2
#define DIOLO  (PORTB &= ~(1<<2))
#define DIOHI  (PORTB |= (1<<2))


class DisplayDriver
{
//variables
public:
protected:
private:

//functions
public:
	DisplayDriver();
	~DisplayDriver();
	void digit(char pos, char value);
	char ReadKeys(void);
	void UpdateKeys(void);
	void UpdateDisplay(void);

protected:
private:
// 	DisplayDriver( const DisplayDriver &c );
// 	DisplayDriver& operator=( const DisplayDriver &c );

char digitsdisplayed[8];
char lastkeysread;
void Shift8bits(char data);
void RunCommand(char command);
void Reset(void);
char dig27seg(char dig);






}; //DisplayDriver

#endif //__DISPLAYDRIVER_H__
