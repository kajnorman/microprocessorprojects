/*
 * LEDnKEY2.cpp
 *
 * Created: 14-10-2019 23:07:27
 * Author : knn
 */ 

// PORTB
#define STB  0
#define STBLO  (PORTB &= ~(1<<0))
#define STBHI  (PORTB |= (1<<0))
#define CLK	 1
#define CLKLO  (PORTB &= ~(1<<1))
#define CLKHI  (PORTB |= (1<<1))
#define DIO	 2
#define DIOLO  (PORTB &= ~(1<<2))
#define DIOHI  (PORTB |= (1<<2))


#include <avr/io.h>

void RunCommand(char command)
{
		STBLO;
		for (int n=0;n<=7;n++)
		{
			CLKLO;
			if (((1<<n) & command) > 0 )
			{
				DIOHI;
			}
			else
			{
				DIOLO;
			}
			
			CLKHI;
		}
		STBHI;
}

void Reset(void)
{
		RunCommand(0x40);
		
		STBLO;
		
		for(int m =0;m<16;m++)
		{
			for (int n=0;n<=7;n++)
			{
				CLKLO;
				if (((1<<n) & 0x00) > 0 )
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
		STBHI;
}

int main(void)
{
	DDRB = 0x07;  //STB, CLK, DIO  is outputs
	
	//Section 5.4 of the datasheet
	//Setting a display controll command  B7=1 B6=0
	//  B5=0 B4=0  
	//  B3=1  =>(Display On)
	// B2,1,0 = 111  Full pulsewidth on display
	//char command = 0b10001111;
	
	
	//Page 9 Transmission format of serial data
	PORTB = 0x07;  //STB, CLK, DIO  are all set to '1'
 		
	
	RunCommand(0b10001000);
	Reset();
	
	
// 	Fromarduinoexample
// 	sendCommand(0x44);  // set single address
// 	digitalWrite(strobe, LOW);
// 	shiftOut(data, clock, LSBFIRST, 0xc0); // 1st digit
// 	shiftOut(data, clock, LSBFIRST, 0xff);
// 	digitalWrite(strobe, HIGH);
	RunCommand(0x44);
	STBLO;
			for (int n=0;n<=7;n++)
			{
				CLKLO;
				if (((1<<n) & 0xC0) > 0 )
				{
					DIOHI;
				}
				else
				{
					DIOLO;
				}
				CLKHI;
			}
			for (int n=0;n<=7;n++)
			{
				CLKLO;
				if (((1<<n) & 0xFF) > 0 )
				{
					DIOHI;
				}
				else
				{
					DIOLO;
				}
				CLKHI;
			}
	STBHI;
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

