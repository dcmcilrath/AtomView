/*
	File:		Triple.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		Definitions of Triple class functions
		Other Triple functions
*/

#include "AVHeaders.hpp"

// Constructors
void Triple::set(double _a, double _b, double _c) { a = _a; b = _b; c = _c; }

Triple::Triple() { set(0, 0, 0); }
Triple::Triple(double _a, double _b, double _c) { set(_a, _b, _c); }

// Switch
Triple Triple::makeCartesian() // assuming state: a -> r, b -> theta, c -> phi
{
	double xy_rad;
	Triple nt;

	nt.c = cos(c)*a;
	xy_rad = sin(c)*a;

	nt.a = cos(b)*xy_rad;
	nt.b = sin(b)*xy_rad;

	return nt;
}

Triple Triple::makePolar() // assuming state: a -> x, b -> y, c -> z
{
	Triple nt;

	nt.a = std::sqrt(a*a + b*b + c*c);
	nt.b = getAngle(a, b, 0, 0);
	nt.c = acos(c/nt.a);

	return nt;
}

// Rotate
void Triple::rotate(char axis, double ro) // assuming state: a -> x, b -> y, c -> z
{
	double a2, b2, c2;

	while (ro < 0 || ro > 2*M_PI)
	{
		if (ro < 0)
			ro += 2*M_PI;
		else
			ro -= 2*M_PI;
	}

	switch (axis)
	{
	case 'x':
		a2 = a;
		b2 = cos(ro)*b - sin(ro)*c;
		c2 = sin(ro)*b + cos(ro)*c;
		break;
	case 'y':
		a2 = cos(ro)*a - sin(ro)*c;
		b2 = b;
		c2 = sin(ro)*a + cos(ro)*c;
		break;
	case 'z':
		a2 = cos(ro)*a - sin(ro)*b;
		b2 = sin(ro)*a + cos(ro)*b;
		c2 = c;
		break;
	}

	a = a2;
	b = b2;
	c = c2;
}

std::string Triple::toPolarString()
{
	std::stringstream ss;
	ss << "Theta: " << degrees(b) << ", Phi: " << degrees(c);
	return ss.str();
}
std::string Triple::toCartString()
{
	std::stringstream ss;
	ss << "X: " << a << ", Y: " << b << ", Z: " << c;
	return ss.str();
}

/*
 *	Other Functions
 */

Triple cross(Triple t1, Triple t2, double alpha)
{
	Triple tnew;
	double f = sin(alpha);
	tnew.a = ( t1.b*t2.c - t1.c*t2.b) / f;
	tnew.b = (-t1.a*t2.c + t1.c*t2.a) / f;
	tnew.c = ( t1.a*t2.b - t1.b*t2.a) / f;

	return tnew;
}

double getAngle(Triple t1, Triple t2)
{
	double mag = t1.a*t2.a + t1.b*t2.b + t1.c*t2.c;
	return acos(mag);
}
