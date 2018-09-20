/*
	File:		Bond.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		December 2013
	Contents:
		Bond class definition
*/

#ifndef BOND_HPP
#define BOND_HPP

class Bond
{
public:
	Element * reference;	// refers to more electronegative atom in bond
	Element * next;

	double rotation;	// bond rotation (added to xy_angle)
	double xy_angle;	// from the negative Element, which direction to move?
	double z_angle;		// add z component due to 3D space

	int multiplicity;	// how many bonds at once? (single/double/triple)

	Bond();
};

Bond * allocateBond();
Bond * allocateBond(Element *, Element *);
Bond * allocateBond(Element *, Element *, double, double);
Bond * allocateBond(Element *, Element *, double, double, int);

#endif
