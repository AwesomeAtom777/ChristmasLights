// SFML Test REAL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <sfml\Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>
#include <fstream>
#include <ctime>
#include "gen.h"
#include "button.h"
#include "textbox.h"
#include "delayer.h"


using namespace std;
using namespace sf;


class EllipseShape : public sf::Shape
{
public:

	explicit EllipseShape(const Vector2f & radius = Vector2f(0, 0)) :
	m_radius(radius)
	{
		update();
	}

	void setRadius(const Vector2f & radius)
	{
		m_radius = radius;
		update();
	}

	const Vector2f & getRadius() const
	{
		return m_radius;
	}

	virtual size_t getPointCount() const
	{
		return 30;
	}

	virtual Vector2f getPoint(std::size_t index) const
	{
		float pi = 3.141592654;
		float angle = index * 2 * pi / getPointCount() - pi / 2;
		float x = cos(angle) * m_radius.x;
		float y = sin(angle) * m_radius.y;

		return sf::Vector2f(m_radius.x + x, m_radius.y + y);
	}

private:

	Vector2f m_radius;
};

vector<vector<CircleShape> > rowvec;
vector<Button> colorButtons;
vector<Color> colors = { Color::White, Color::Blue, Color::Red, Color::Green, Color::Yellow };
Font arial;
Text inv;
Delayer invalShow(3, 1);

void sayInval(string message)
{
	invalShow.reset();
	if(inv.getString() == "INVALID!")
		inv.setString("INVALID! " + message);
}

void formLights(int rep)
{
	rowvec.clear();
	for (int k = 0; k < rep; k++)
	{
		vector<CircleShape> light;
		for (int i = 0; i < 7; i++)
		{
			CircleShape l1;
			l1.setFillColor(Color::Black);
			l1.setOutlineColor(Color::White);
			l1.setOutlineThickness(1);
			l1.setPosition(300 + 23 * i, 20 + 23 * k);
			l1.setRadius(10);
			light.push_back(l1);
		}
		rowvec.push_back(light);
	}
}
Button setcol;
Button startstop;

vector<Button*> subsys;

void checkSubs(RenderWindow& wind)
{
	
	for (int i = 0; i < subsys.size(); i++)
	{
		if (subsys[i]->help.checkIfSub(wind))
		{
			subsys[i]->help.showHelp = !subsys[i]->help.showHelp;
		}
	}
}


int main()
{
	cout << "hi" << endl;
	RenderWindow window(VideoMode(750, 500), "SFML Test", Style::Close | Style::Resize);
	long double interval = 1;
	Color curcol = Color::White;

	Delayer lighter(1, 0);

	cout << "hi" << endl;

	arial.loadFromFile("C:\\Users\\pcsom\\source\\repos\\Tests\\SFML Test REAL\\Debug\\Arial.ttf");

	startstop.setFillColor(Color::Green);
	startstop.setPosition(100, 200);
	startstop.instruct.setString("Start or stop the display.");
	startstop.help = SubButton(180, 207);
	startstop.desc.setString("Start/Stop");
	startstop.desc.setCharacterSize(13);
	startstop.desc.setPosition({ 100, 185 });
	subsys.push_back(&startstop);

	setcol.setFillColor(Color::White);
	setcol.setPosition(210, 200);
	setcol.instruct.setString("Set the color by clicking the button and then clicking a colored button in the drop-down.");
	setcol.help = SubButton(291, 207);
	setcol.desc.setString("Set Color");
	setcol.desc.setCharacterSize(13);
	setcol.desc.setPosition({ 210, 185 });
	subsys.push_back(&setcol);

	formLights(1);

	inv.setCharacterSize(15);
	inv.setFont(arial);
	inv.setFillColor(Color::White);
	inv.setString("INVALID!");
	inv.setPosition({ 10,450 });

	int colorctr = 0, rowctr = 0;
	bool running = 1, showColorMenu = 0;

	for (int k = 0; k < 5; k++)
	{
		Button a;
		a.setFillColor(colors[k]);
		a.setPosition(210, 200+35*(k+1));
		a.setSize(Vector2f(100, 30));
		colorButtons.push_back(a);
	}

	TextBox rows = TextBox(15, Color::White, false);
	rows.setPosition({ 325, 245 });
	rows.activate.setPosition({ 320, 240 });
	rows.activate.setFillColor(Color::Blue);
	rows.activate.instruct.setString("Select the number of rows of lights. Enter a integer between 1 and 7, inclusive");
	rows.activate.help = SubButton(401, 248);
	rows.setLimit(1, 1);
	rows.activate.desc.setString("Set Rows");
	rows.activate.desc.setCharacterSize(13);
	rows.activate.desc.setPosition({ 320, 270 });
	subsys.push_back(&(rows.activate));

	TextBox textbox1 = TextBox(15, Color::White, false);
	textbox1.setPosition({ 325, 205 });
	textbox1.activate.setPosition({ 320, 200 });
	textbox1.activate.setFillColor(Color::Blue);
	textbox1.activate.setSize({ 200, 30 });
	textbox1.activate.instruct.setString("Select the time interval between each light movement. Enter an integer or decimal.");
	textbox1.activate.help = SubButton(500, 207);
	textbox1.setLimit(1, 10);
	textbox1.activate.desc.setString("Set Time Interval");
	textbox1.activate.desc.setCharacterSize(13);
	textbox1.activate.desc.setPosition({ 320, 185 });
	subsys.push_back(&(textbox1.activate));


	while (window.isOpen())
	{
		Event event;


		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();

			case Event::TextEntered:
				textbox1.typedOn(event);
				rows.typedOn(event);
			}
		}
		window.clear();






		if (rows.activate.checkIfClicked(window))
		{
			if (!rows.getSelected())
				rows.setSelected(true);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Escape) || rows.activate.clickedOut(window))
		{
			rows.setSelected(false);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			if (rows.getSelected())
			{
				if (isDig(rows.getText()[0]) && inRange(rows.getText()[0], '1', '7', true))
				{
					sleep(0.3);
					formLights(int(rows.getText()[0] - '0'));
				}
				else
				{
					sayInval("Enter an integer between 1 and 7, inclusive.");
				}
			}
		}

		if (textbox1.activate.checkIfClicked(window))
		{
			if (!textbox1.getSelected())
				textbox1.setSelected(true);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Escape) || textbox1.activate.clickedOut(window))
		{
			textbox1.setSelected(false);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			if (textbox1.getSelected())
			{
				string newint = textbox1.getText();
				if (verifyNum(newint))
				{
					interval = stold(newint);
					lighter.setInter(interval);
					cout << "changed interval" << endl;
					sleep(0.3);
				}
				else
				{
					sayInval("Enter an integer or decimal number.");
				}
			}
		}



		colorctr %= rowvec.size()*7;



		if (startstop.checkIfClicked(window))
		{
			running = !running;
		}

		if (setcol.checkIfClicked(window))
		{
			showColorMenu = !showColorMenu;
		}

		if (running)
		{
			if (!lighter.inTime(1))
			{
				for (int i = 0; i < rowvec.size(); i++)
				{
					for (int k = 0; k < 7; k++)
					{
						rowvec[i][k].setFillColor(Color::Black);
						if (k == colorctr%7 && i == int(colorctr/7))
						{
							rowvec[i][k].setFillColor(curcol);
						}
					}
				}
				colorctr++;
			}
		}
		else
		{
			for (auto& j : rowvec)
			{
				for (int i = 0; i < 7; i++)
				{
					j[i].setFillColor(Color::Black);
				}
			}
		}
		if (showColorMenu)
		{
			for (auto curColBut : colorButtons)
			{
				window.draw(curColBut);
				if (curColBut.checkIfClicked(window))
				{
					curcol = curColBut.getFillColor();
					setcol.setFillColor(curcol);
				}
			}
		}
		checkSubs(window);
		
		for (int z = 0; z < subsys.size(); z++)
		{
			if (subsys[z]->help.clickedOut(window))
			{
				subsys[z]->help.showHelp = 0;
			}
		}

		for (auto curVec : rowvec)
			for (auto curLight : curVec)
				window.draw(curLight);
		window.draw(startstop);
		window.draw(setcol);
		window.draw(textbox1.activate);
		textbox1.drawTo(window);
		window.draw(rows.activate);
		rows.drawTo(window);
		if (invalShow.inTime(0))
			window.draw(inv);
		else
			inv.setString("INVALID!");
		
		for (int z = 0; z < subsys.size(); z++)
		{
			window.draw(subsys[z]->help);
			window.draw(subsys[z]->help.desc);
			window.draw(subsys[z]->desc);
			if (subsys[z]->help.showHelp)
			{
				window.draw(subsys[z]->instruct);
			}
		}
		window.display();
	}
	return 0;
}
