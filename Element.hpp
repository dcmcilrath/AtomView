/*
	File:		Element.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		Element subclass of group, holds one atom
*/

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

class Element : public Group
{
public:

	int z;								// atomic number
	DrawingObject * associated;					// associated drawingobject for rendering
	std::vector<Bond *> bonds;					// bonds to other atoms

	std::string name;						// description of atom (group, position)

	Element();
	virtual void setUpRendering(double, double, double, Triple);	// inherited from Group
};

Element * allocateElement();
Element * allocateElement(int);
Element * allocateElement(int, std::string);

#endif
