/*
 * SoftwaretestofHardware.cpp
 *V1	Software test of hardware
 * Created: 19-02-2019 09:48:25
 * Author : knn
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)  //
{
	unsigned char A = 0;
    DDRB = 0xff;
    while (1) 
    {
		PORTB=A;
		_delay_ms(500);
		A++;
    }
}

