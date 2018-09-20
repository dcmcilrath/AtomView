/*
	File:		Color.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		December 2013
	Contents:
		Color class
*/

#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
public:
	double Red;
	double Green;
	double Blue;

	Color();
	Color(double, double, double);
	Color(std::string);

	void set(double, double, double);	// set manually the rgb values
	void set(std::string);			// takes string like "red" and assigns appropriate values (e.g. 1, 0, 0)

	void scale(double);			// scale the color by a factor (for making darker, lighter)

	void makeDrawingColor();		// call glColor3d() with Red, Green, and Blue values for this color
};

#endif
