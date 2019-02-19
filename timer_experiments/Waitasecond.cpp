 /* wait a sec
 *
 * Created: 19-02-2019 13:27:23
 * Author : knn
 */ 


#define F_CPU 8000000
#include <avr/io.h>

unsigned char sec=0;

int main(void)  //
{
	DDRB = 0xff;

	// 8 MHz prescaler is 1024
	TCCR1B |= (1<<CS12)|(1<<CS10);  //0b00000101
	
	
	while (1)
	{
		if (TCNT1 >= 7812)   //1 second
		{
			TCNT1 =0;
			sec++;
		}
		PORTB = sec;
	}
}

