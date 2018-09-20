/*
	File:		Anchor.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		March 2014
	Contents:
		Anchor class which describes how to connect two Groups
*/

#ifndef ANCHOR_HPP
#define ANCHOR_HPP

class Anchor
{
private:
	void bond(Element *);				// preforms all steps common to both attach functions

public:
	Group * group;					// pointer to group
	Element * terminal;				// element to be part of inter-group bond
	int bond_index;					// location of the bond in terminal to be deleted
	int swap_index;					// location of the element in group to be deleted

	Anchor();
	Anchor(Group *, Element *, int, int);

	void set(Group *, Element *, int, int);

	void attach(Anchor);				// use this anchor as a base, and "other" as subgroup
	void attach(Element *);				// attach a single element instead of an entire group
};

// helping functions
Anchor makeAnchor(Group *, Element *, Bond *);		// sets group and element as specified, then
							// resolves indicies for the Bond *

Anchor makeDoubleAnchor(Group *, Element *, Bond *, Bond *);
							// similar to makeAnchor but deletes second bond and adjusts angles

#endif
