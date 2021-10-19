/* 
* ChessClock.h
*
* Created: 26-11-2019 21:51:05
* Author: knn
*/
#include "DisplayDriver.h"
#include "Time.h"

#ifndef __CHESSCLOCK_H__
#define __CHESSCLOCK_H__


class ChessClock
{
//variables
private:
enum state {Stopped,WhitePlays,BlackPlays} ChessClockState;
Time white;
Time black;
DisplayDriver DD;
//functions
public:
ChessClock();
~ChessClock();
void IsrMethod(void);// shall be run every 10 millisec
void RunTheClock();
private:
void ShowBlackTime(void);
void ShowWhiteTime(void);
}; //ChessClock

#endif //__CHESSCLOCK_H__
