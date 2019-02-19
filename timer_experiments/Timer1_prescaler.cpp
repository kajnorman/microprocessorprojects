/*
 * Timer1_prescaler.cpp
 *
 * Created: 19-02-2019 13:27:23
 * Author : knn
 */ 


#define F_CPU 8000000
#include <avr/io.h>

unsigned int TimerValue;  // an unsigned int is used to read two 8-bit registers

int main(void)  //
{
	DDRB = 0xff;

	// 8 MHz prescaler is 1024
	TCCR1B |= (1<<CS12)|(1<<CS10);  //0b00000101
	
	
	while (1)
	{
		TimerValue = TCNT1;  
		PORTB = TimerValue>>8;    // 8 msbits from timer 1
	}
}

