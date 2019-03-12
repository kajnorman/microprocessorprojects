/*
 * IOlib.h
 *
 * Created: 08-03-2019 15:00:31
 *  Author: knn
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

class PINonPORTB
{
	public:
	PINonPORTB(unsigned char n)
	{
		portnumber = n;
	}
		
	private:
	unsigned char portnumber;	
};


class OUTonPORTB     // : public PINonPORTB
{
	public:
	OUTonPORTB(unsigned char n);  //constructor takes portb-bit nr as input
	void activate(bool flag);  // sets the output value on pin to hi if flag is true
	private:
	unsigned char portnumber;
};

class BUTonPORTB
{
	public:
	BUTonPORTB(unsigned char n);  //sets PORTB.n to be an input Buuton connected to ground
	bool pressed();  //  gets the immediate status of Button n....true for being pressed
	private:
	unsigned char portnumber;
};




#endif /* INCFILE1_H_ */