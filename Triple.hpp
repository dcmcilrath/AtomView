/*
	File:		Triple.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		Triple class definition
		Other Triple functions
*/

#ifndef TRIPLE_HPP
#define TRIPLE_HPP

/*
 *	The Triple is like a 1x3 matrix which can either describe polar or cartesian coordinates in 3D
 */

class Triple
{
public:
	double a;
	double b;
	double c;

	// Constructors
	Triple();
	Triple(double, double, double);

	void set(double, double, double);

	// Switch
	Triple makeCartesian();
	Triple makePolar();

	// Rotate (requires cartesian)
	void rotate(char, double);		// takes (x/y/z) for axis and an angle

	// toString
	std::string toPolarString();		// for debugging
	std::string toCartString();
};

Triple cross(Triple, Triple, double);		// compute cross product
double getAngle(Triple, Triple);		// get minimum planar angle between two vectors

#endif
