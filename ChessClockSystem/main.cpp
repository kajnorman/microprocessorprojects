/*
 * main.cpp
 *chess clock
 * Created: 26-10-2019 19:58:00
 * Author : knn
 */ 
#define F_CPU   8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ChessClock.h"

	
ChessClock CC = ChessClock();


void timer1_init() //0.01-second interrupt  (TM1638( uses 4.7 msec)-- initialize timer, interrupt and variable
//  wit a prescaler of 8 the count in 0.01 sec is 
//  echo $((8000000/8/100))
//  10000
//  So the initialvalue for the timer should be 
//  echo $((2**16-8000000/8/100))
//  55536
//CS 12,11,10 = 0,1,0
{
	// set up timer with prescaler = 8
	TCCR1B |= (1 << CS11);
	// initialize counter
	TCNT1 = 55536;
	// enable overflow interrupt
	TIMSK1 |= (1 << TOIE1);
	// enable global interrupts

	sei();
}

// TIMER1 overflow interrupt service routine
ISR(TIMER1_OVF_vect)
{
	TCNT1 = 55536;
	CC.IsrMethod();

}

int main(void)
{
	DDRC |= (1 << 0);	// connect led to pin PC0 for "ticking"
	timer1_init(); 	// initialize timer
	while(1)
		CC.RunTheClock();

	
}
