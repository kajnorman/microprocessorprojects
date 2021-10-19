/* 
* Time.cpp
*
* Created: 10-10-2019 11:00:46
* Author: knn
*/


#include "Time.h"

// default constructor
Time::Time()
{
	hour=0;
	minute=0;
	second=0;
} //Time

Time::Time(signed char h,signed char m,signed char s)
{
	hour=h;
	minute=m;
	second=s;
} //Time





void Time::Decr1sec_and_adjust_accordingly(void)
{
	second--;
	if (second<0) 
	{
		second=59;
		minute--;
		if (minute<0)
		{
			minute = 59;
			hour--;
			if (hour<0)
			{
				hour = 23;
			}
		}		
	}
}

void Time::Add1sec_and_adjust_accordingly(void)
{
	second++;
	if (second >59)
	{
		minute++;
		second= 0;
		if (minute >59)
		{
			hour++;
			minute= 0;
			if (hour >23)
			{
				
				hour= 0;
			}

		}

	}
	
}

char Time::GetHour(void)
{
	return hour;
}
char Time::GetMinute(void)
{
	return minute;
}

char Time::GetSecond(void)
{
	return second;
}
