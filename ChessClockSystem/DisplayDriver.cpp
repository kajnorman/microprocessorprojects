/* 
* DisplayDriver.cpp
*
* Created: 19-10-2019 22:02:20
* Author: knn
*/


#include "DisplayDriver.h"

// default constructor
DisplayDriver::DisplayDriver()
{
	DDRB = 0x07;  //STB, CLK, DIO  is outputs
	PORTB = 0x07;  //STB, CLK, DIO  are all set to '1'
	Reset();	
	RunCommand(0x8F);  //display ON  prw 14/16 
	for (unsigned char n=0;n<8;n++) digitsdisplayed[n]=0x08;//0x0A; //invalid digit  shows as blank  
} //DisplayDriver

void DisplayDriver::digit(char pos, char value)
{
	digitsdisplayed[pos]=value;
// 	RunCommand(0x8F);  //display ON  prw 14/16  //not needed if line is stable
// 
// 	//position 0<=> leftmost  7<=> rightmost
// 	//address =  (pos * 2) + 0xC0;
// 	RunCommand(0x44);  //ADDR + data
// 	STBLO;
// 	Shift8bits((pos * 2)+0xC0);  
// 	Shift8bits(dig27seg(value));   //conversion not ready
// 	STBHI;
}

void DisplayDriver::UpdateDisplay(void)
{
	RunCommand(0x8F);  //display ON  prw 14/16  //not needed if line is stable	
	for (unsigned char n=0;n<8;n++)
	{
			//position 0<=> leftmost  7<=> rightmost
			//address =  (pos * 2) + 0xC0;
			RunCommand(0x44);  //ADDR + data
			STBLO;
			Shift8bits((n * 2)+0xC0);//n is the position
			Shift8bits(dig27seg(digitsdisplayed[n]));   //conversion not ready
			STBHI;
	}
}


void DisplayDriver::UpdateKeys(void)
{
	//set strobe low
	//send 0x42 (use shift8bits)
	//change DIO DDR to input
	//repeat 4 times
		//repeat 8 times
		//		set clk hi
		//		read databit (Start D0  end D7)
		//		set clk lo
	//set STB hi
	//change DIO DDR to output
	char totalvalue=0;
	char value[4];
	
	for (unsigned char n=0;n<=3;n++)
	{
		value[n]=0;
	}
	STBLO;
	Shift8bits(0x42);
	DDRB &= ~(1<<DIO);
	for(unsigned char m=0;m<=3;m++)
	{
		for(unsigned char n=0;n<=7;n++)
		{
			CLKHI;
			char bit = !!(PINB & (1<<2));
			value[m] |= (bit<<n);
			CLKLO;
		}
	}
	STBHI;
	DDRB |= (1<<DIO);
	for (unsigned char n=0;n<=3;n++)
	{
		if (value[n] & (1<<1)) totalvalue |= (1<<n);
		if (value[n] & (1<<5)) totalvalue |= (1<<(n+4));
	}
	lastkeysread= totalvalue;	
}



char DisplayDriver::ReadKeys(void) //Returns  8 bit pattern : S1 lsb,S2->S7,S8 msb
{	
	return lastkeysread;
}


char DisplayDriver::dig27seg(char dig)
{
	if (dig==1) return 0x06;
	if (dig==2) return 0x5B;
	if (dig==3) return 0x4F;
	if (dig==4) return 0x66;
	if (dig==5) return 0x6D;
	if (dig==6) return 0x7D;
	if (dig==7) return 0x07;
	if (dig==8) return 0x7F;
	if (dig==9) return 0x6F;
	if (dig==0) return 0x3F;
	return 0x00;
}
 
// default destructor
DisplayDriver::~DisplayDriver()
{
} //~DisplayDriver


void DisplayDriver::Shift8bits(char data)
{
	for (int n=0;n<=7;n++)
	{
		CLKLO;
		if (((1<<n) & data) > 0 )
		{
			DIOHI;
		}
		else
		{
			DIOLO;
		}
		CLKHI;
	}
}

void DisplayDriver::RunCommand(char command)
{
	STBLO;
	Shift8bits(command);
	STBHI;
}

void DisplayDriver::Reset(void)
{
	RunCommand(0x40);
	STBLO;
	for(int m =0;m<16;m++)
	{
		Shift8bits(0x00);
	}
	STBHI;
}