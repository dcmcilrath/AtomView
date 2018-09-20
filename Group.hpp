/*
	File:		Group.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		Group class which may represent a functional group, chain, or an entire molecule
		Allocation functions
*/

#ifndef GROUP_HPP
#define GROUP_HPP

class Group
{
public:
	std::vector<Group *> subgroups;					// Elements or Groups in this group

	// Constructors
	Group();

	int configureGroup();						// determine configuration of bonds between elements in group
	virtual void setUpRendering(double, double, double, Triple);	// create drawingObjects for group
};

// Allocate group and return pointer
Group * allocateGroup();

// Determine molecular formula
std::string determineFormula(Group *);

#endif
