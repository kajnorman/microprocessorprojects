/**
 * sounddata from  DR archive
 resampled to 
 resolution 8-bit
 samplerate 8kHz
 output using the 8-Bit Fast PWM mode. timer1 (a waste of bits)
  * Created: 13-03-2019 15:29:20
  *  Author: knn
  *  sound output is at PB1  (pin 15 on DIP-device). 
 */
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/pgmspace.h>


#include "Comet.h"

int main (void) {


	DDRB |= (1<<PORTB1); 

	TCCR1A |= (1<<COM1A1) | (1<<WGM10);
	TCCR1B |= (1<<CS10) | (1<<WGM12);


while(1)
	{
	for(unsigned int n = 0 ; n<=5053;n++) {
                                
		OCR1A = (pgm_read_byte(&sounddata_data[n]));
		_delay_us(125);
	   }
	_delay_ms(500);
	}
}
