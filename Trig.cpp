/*
	File:		Trig.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		December 2013
	Contents:
		Math functions used by multiple different parts of program:
			radians
			getDistance
			getAngle
*/

#include "AVHeaders.hpp"

double radians(double degrees) { return degrees * M_PI / 180; }

double degrees(double radians) { return radians * 180 / M_PI; }

double getDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

double getAngle(double x1, double y1, double x2, double y2)
{
	double x = x1-x2;
	double y = y1-y2;

	if (x < .00000000001 && x > -.00000000001)
		x = 0;
	if (y < .00000000001 && y > -.00000000001)
		y = 0;

	if (x == 0 && y == 0)
		return 0;

	double radians;
	double h = getDistance(x1, y1, x2, y2);

	if (x >= 0)
		radians = asin(y/h);
	else
		radians = M_PI - asin(y/h);

	while (radians >= 2*M_PI)
		radians -= 2*M_PI;
	while (radians < 0)
		radians += 2*M_PI;

	return radians;
}
