#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>
#include <fstream>
#include <ctime>

#include "gen.h"
#include "delayer.h"

using namespace sf;
using namespace std;

Font arial1;


class SubButton : public RectangleShape
{
public:
	SubButton()
	{
		setFillColor(Color::Black);
		setOutlineColor(Color::White);
		setSize({ 15, 15 });
		desc.setCharacterSize(13);
		desc.setFillColor(Color::White);
		desc.setString("?");
		arial1.loadFromFile("C:\\Users\\pcsom\\source\\repos\\Tests\\SFML Test REAL\\Debug\\Arial.ttf");
		desc.setFont(arial1);
		clickDet = Delayer(0.3, 1);
	}
	SubButton(float xy, float yy)
	{
		setFillColor(Color::Black);
		setOutlineColor(Color::White);
		setOutlineThickness(1);
		setSize({ 15, 15 });
		setPosition({ xy, yy });
		desc.setCharacterSize(13);
		desc.setFillColor(Color::White);
		desc.setString("?");
		desc.setPosition({ xy + 4, yy - 1 });
		arial1.loadFromFile("C:\\Users\\pcsom\\source\\repos\\Tests\\SFML Test REAL\\Debug\\Arial.ttf");
		desc.setFont(arial1);
		clickDet = Delayer(0.3, 1);
	}
	bool checkIfSub(RenderWindow& window)
	{
		if (!clickDet.inTime(0))
		{
			Vector2i mousepos = Mouse::getPosition(window);
			bool finalDec = inRange_(mousepos.x, getPosition().x + 0, getPosition().x + getSize().x, true) && inRange_(mousepos.y, getPosition().y + 0, getPosition().y + getSize().y, true) && Mouse::isButtonPressed(Mouse::Left);
			if (finalDec)
			{
				clickDet.reset();
			}
			return finalDec;
		}
		else
		{
			return false;
		}
		
	}
	bool checkIfSub(RenderWindow& window, bool deb)
	{
		Vector2i mousepos = Mouse::getPosition(window);
		bool finalDec = inRange_(mousepos.x, getPosition().x + 0, getPosition().x + getSize().x, true) && inRange_(mousepos.y, getPosition().y + 0, getPosition().y + getSize().y, true) && Mouse::isButtonPressed(Mouse::Left);
		return finalDec;
	}
	bool clickedOut(RenderWindow& window)
	{
		Vector2i mousepos = Mouse::getPosition(window);
		return (!inRange_(mousepos.x, getPosition().x + 0, getPosition().x + getSize().x, true) || !inRange_(mousepos.y, getPosition().y + 0, getPosition().y + getSize().y, true)) && Mouse::isButtonPressed(Mouse::Left);
	}
	bool showHelp = false;
	Text desc;
protected:
	Delayer clickDet;
	template<class U, class V, class W>
	bool inRange_(U check, V low, W high, bool inclusive)
	{
		if (inclusive)
			return check >= low && check <= high;
		else
			return check > low && check < high;
	}
	/*void setHelpPos(anchorHelpX xRaw, anchorHelpY yRaw, int setX, int setY)
	{
		float xFinal, yFinal;
		switch (xRaw)
		{
		case Right:
			xFinal = 
		}
	}*/
private:
};

class Button : public SubButton
{
public:
	Button()
	{
		setFillColor(Color::White);
		setPosition(100, 100);
		setSize(Vector2f(100, 30));
		arial1.loadFromFile("C:\\Users\\pcsom\\source\\repos\\Tests\\SFML Test REAL\\Debug\\Arial.ttf");
		desc.setFont(arial1);
		desc.setPosition({ 100, 100 });
		desc.setCharacterSize(15);
		desc.setFillColor(Color::White);
		desc.setString("SET DESCRIPTION");
		instruct.setFont(arial1);
		instruct.setPosition({ 10,470 });
		instruct.setCharacterSize(15);
		instruct.setFillColor(Color::White);
		instruct.setString("SET INSTRUCTION");
		help = SubButton(100, 100);
		clickDet = Delayer(0.3, 1);
	}
	bool checkIfClicked(RenderWindow& window)
	{
		if (!clickDet.inTime(0))
		{
			Vector2i mousepos = Mouse::getPosition(window);
			bool finalDec = inRange_(mousepos.x, getPosition().x + 0, getPosition().x + getSize().x, true) && inRange_(mousepos.y, getPosition().y + 0, getPosition().y + getSize().y, true) && Mouse::isButtonPressed(Mouse::Left) && !help.checkIfSub(window, 1);
			if (finalDec)
			{
				clickDet.reset();
			}
			return finalDec;
		}
		else
		{
			return false;
		}
	}
	Text instruct;
	SubButton help;
	
protected:
private:
};
