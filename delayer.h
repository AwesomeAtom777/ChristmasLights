#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>
#include <fstream>
#include <ctime>

using namespace std;

class Delayer
{
public:
	Delayer()
	{

	}
	Delayer(long double inter_, bool skip)
	{
		inter = inter_;
		secondsMore = inter * CLOCKS_PER_SEC;
		if (skip)
			startingClock = clock() - (secondsMore + 1);
		else
			startingClock = clock();
	}
	bool inTime(bool re)
	{
		if (clock() >= startingClock + secondsMore)
		{
			if (re)
				reset();
			return false;
		}
		else
		{
			return true;
		}
	}
	void setInter(long double inter_)
	{
		inter = inter_;
		secondsMore = inter * CLOCKS_PER_SEC;
	}
	void reset()
	{
		startingClock = clock();
	}
private:
	clock_t startingClock;
	long double secondsMore;
	long double inter;
};