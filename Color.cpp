/*
	File:		Color.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		December 2013
	Contents:
		Color class functions
*/

#include "AVHeaders.hpp"

Color::Color() { set(0, 0, 0); }
Color::Color(double r, double g, double b) { set(r, g, b); }
Color::Color(std::string colorname) { set(colorname); }

void Color::set(double r, double g, double b)
{
	Red = r;
	Green = g;
	Blue = b;
}
void Color::set(std::string colorname)
{
	if (colorname == "red" 		|| colorname == "Red"	)	set(1, 0, 0);
	if (colorname == "green" 	|| colorname == "Green"	)	set(0, 1, 0);
	if (colorname == "blue" 	|| colorname == "Blue"	) 	set(0, 0, 1);
	if (colorname == "white" 	|| colorname == "White"	)	set(1, 1, 1);
	if (colorname == "grey" 	|| colorname == "Grey"	) 	set(0.5, 0.5, 0.5);

	// default ("black")
	set(0, 0, 0);
}

void Color::scale(double scalar)
{
	Red *= scalar;
	Green *= scalar;
	Blue *= scalar;
}

void Color::makeDrawingColor() { glColor3d(Red, Green, Blue); }
