#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <utility>
#include <fstream>
#include <ctime>
#include "gen.h"

using namespace std;

void sleep(long double secs)
{
	clock_t startClock2 = clock();
	float secondsAhead2 = secs * CLOCKS_PER_SEC;
	while (clock() < startClock2 + secondsAhead2);
	return;
}

bool isDig(char a)
{
	return a <= '9' && a >= '0';
}

bool verifyNum(string check)
{
	int pers = 0;
	if (check.length() == 0)
	{
		return false;
	}
	for (auto i : check)
	{
		if (i == '.')
		{
			pers += 1;
		}
		else if (isDig(i))
		{
			continue;
		}
		else
			return false;
	}
	if (pers > 1)
		return false;
	return true;
}

