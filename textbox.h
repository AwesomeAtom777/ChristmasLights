#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "button.h"

#define DELETE_KEY 8
#define ESCAPE 27
#define ENTER 13

using namespace sf;
using namespace std;



class TextBox
{
public:

	TextBox()
	{

	}

	TextBox(int size, Color color, bool sel)
	{
		arial1.loadFromFile("C:\\Users\\pcsom\\source\\repos\\Tests\\SFML Test REAL\\Debug\\Arial.ttf");
		textbox.setFont(arial1);
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;
		if (sel)
		{
			textbox.setString("_");
		}
		else
		{
			textbox.setString("");
		}
	}

	void setFont(Font& font)
	{
		textbox.setFont(font);
	}

	void setPosition(Vector2f pos)
	{
		textbox.setPosition(pos);
	}

	void setLimit(bool ToF)
	{
		hasLimit = ToF;
	}

	void setLimit(bool ToF, int lim)
	{
		hasLimit = ToF;
		limit = lim - 1;
	}

	void setSelected(bool sel)
	{
		isSelected = sel;
		if (!sel)
		{
			string t = text.str();
			string newT = "";
			for (int i = 0; i < t.length(); i++)
			{
				newT += t[i];
			}
			textbox.setString(newT);
		}
		else
		{
			inputLogic(129);
		}
	}

	bool getSelected()
	{
		return isSelected;
	}

	string getText()
	{
		return text.str();
	}

	void drawTo(RenderWindow &window)
	{
		window.draw(textbox);
	}

	void typedOn(Event input)
	{
		if (isSelected)
		{
			int charTyped = input.text.unicode;
			if (charTyped < 128)
			{
				if (hasLimit)
				{
					if (text.str().length() <= limit)
					{
						inputLogic(charTyped);
					}
					else if (text.str().length() > limit && charTyped == DELETE_KEY)
					{
						deleteLastChar();
					}
				}
				else
				{
					inputLogic(charTyped);
				}
			}
		}
	}

	void clear()
	{
		int leng = text.str().length();
		for (int i = 0; i < leng; i++)
		{
			deleteLastChar();
		}
	}

	Button activate;

private:
	Text textbox;
	ostringstream text;
	bool isSelected = 0, hasLimit = 0;
	int limit;

	void inputLogic(int charTyped)
	{
		if (charTyped != DELETE_KEY && charTyped != ESCAPE && charTyped != 129 && charTyped != ENTER)
		{
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY)
		{
			if (text.str().length() > 0)
			{
				deleteLastChar();
			}
		}
		textbox.setString(text.str() + "_");
	}

	void deleteLastChar()
	{
		string t = text.str();
		string newT = "";
		for (int i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		text.str("");
		text << newT;

		textbox.setString(text.str());
	}
};