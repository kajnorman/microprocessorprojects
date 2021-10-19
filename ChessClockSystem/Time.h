/* 
* Time.h
*
* Created: 10-10-2019 11:00:46
* Author: knn
*/


#ifndef __TIME_H__
#define __TIME_H__


class Time
{
//variables
public:
signed char  hour,minute,second;//char is unsigned by default
protected:
private:


//functions
public:
	Time();
	Time(signed char  h,signed char m,signed char s);
	
	char GetHour(void);
	char GetMinute(void);
	char GetSecond(void);



void	Add1sec_and_adjust_accordingly(void);
void	Decr1sec_and_adjust_accordingly(void);

protected:
private:


}; //Time

#endif //__TIME_H__
