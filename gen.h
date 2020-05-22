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

enum anchorHelpX { Left, Center, Right };
enum anchorHelpY { Top, Middle, Bottom };

using namespace std;

void sleep(long double secs);

bool verifyNum(string check);

bool isDig(char a);

template<class U, class V, class W>
bool inRange(U check, V low, W high, bool inclusive)
{
	if (inclusive)
		return check >= low && check <= high;
	else
		return check > low && check < high;
}