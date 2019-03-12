/*
 * IOlib.h
 *
 * Created: 08-03-2019 15:00:31
 *  Author: knn
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

//prototypes later to be the header
void setupLEDonPORTB(unsigned char n);  //sets PORTB.n to be an output
void setupBUTonPORTB(unsigned char n);  //sets PORTB.n to be an input Buuton connected to ground
bool getBUT(unsigned char n);  //  gets the immediate status of Button n....true for being pressed
void setLED(unsigned char n, bool flag);  // sets the output value on pin PORTB.n. High if flag is true




#endif /* INCFILE1_H_ */