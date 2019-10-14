/*
 * LEDnKEY.cpp
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




int main(void)
{
	DDRB = 0x07;  //STB, CLK, DIO  is outputs
	
	//Section 5.4 of the datasheet
	//Setting a display controll command  B7=1 B6=0
	//  B5=0 B4=0  
	//  B3=1  =>(Display On)
	// B2,1,0 = 111  Full pulsewidth on display
	
	//Page 9 Transmission format of serial data
	PORTB = 0x07;  //STB, CLK, DIO  are all set to '1'
	
	STBLO;

	CLKLO;
	DIOHI; //B0 = 1
	CLKHI;
	
	CLKLO;
	DIOHI; //B1 = 1
	CLKHI;
	
	CLKLO;
	DIOHI; //B2 = 1
	CLKHI;
	
	CLKLO;
	DIOHI; //B3 = 1
	CLKHI;
	
	CLKLO;
	DIOLO; //B4 = 0
	CLKHI;
	
	CLKLO;
	DIOLO; //B5 = 0
	CLKHI;
	
	CLKLO;
	DIOLO; //B6 = 0
	CLKHI;
	
	CLKLO;
	DIOHI; //B7 = 1
	CLKHI;
	
	STBHI;
	
	
	
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

