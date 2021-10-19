/* 
* ChessClock.cpp
*
* Created: 26-11-2019 21:51:05
* Author: knn
*/


#include "ChessClock.h"



// default constructor
ChessClock::ChessClock()
{
	white = Time(0,5,0);
	black = Time(0,5,0);
	DD = DisplayDriver();
	ChessClockState = WhitePlays;
	ShowWhiteTime();
	ShowBlackTime();
} //ChessClock

// default destructor
ChessClock::~ChessClock()
{
} //~ChessClock



void ChessClock::ShowWhiteTime(void)
{
				char m=white.GetMinute();
				char s=white.GetSecond();
				DD.digit(4,m/10);
				DD.digit(5,m%10);
				DD.digit(6,s/10);
				DD.digit(7,s%10);
}

void ChessClock::ShowBlackTime(void)
{
				char m=black.GetMinute();
				char s=black.GetSecond();
				DD.digit(0,m/10);
				DD.digit(1,m%10);
				DD.digit(2,s/10);
				DD.digit(3,s%10);
}


void ChessClock::IsrMethod(void)// to be run each 10 milliseconds
{
	DD.UpdateKeys();	
	static char divider = 0;
	if (divider>=100)
	{
		PORTC  =  ~(PORTC);
		divider = 0;
		if (ChessClockState == WhitePlays) 
			{
				white.Decr1sec_and_adjust_accordingly();
				ShowWhiteTime();
			}
		if (ChessClockState == BlackPlays) 
			{
				black.Decr1sec_and_adjust_accordingly();
				ShowBlackTime();
			}
		DD.UpdateDisplay();
	}
	divider += 1;

}


void ChessClock::RunTheClock()
{
	if ((DD.ReadKeys() & 0b11000000)>0)
	{
		ChessClockState = Stopped; //S7
	}
	if ((DD.ReadKeys() & 0b00110000)>0)
	{
		ChessClockState = WhitePlays; //S5
	}
	if ((DD.ReadKeys() & 0b00001100)>0)
	{
		ChessClockState = BlackPlays; //S3
	}
	if ((DD.ReadKeys() & 0b00000011)>0)
	{
		// reset;
		white = Time(0,5,0);
		black = Time(0,5,0);
	}
}