/*
	File:		Anchor.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		March 2014
	Contents:
		Anchor class function definitions
*/

#include "AVHeaders.hpp"

Anchor::Anchor() { group = NULL; terminal = NULL; bond_index = 0; swap_index = 0; }
Anchor::Anchor(Group * g, Element * e, int bi, int si) { set(g, e, bi, si); }

void Anchor::set(Group * g, Element * e, int bi, int si) { group = g; terminal = e; bond_index = bi; swap_index = si; }

void Anchor::bond(Element * e)
{
	// get angles
	double xy_angle = terminal->bonds.at(bond_index)->xy_angle;
	double z_angle = terminal->bonds.at(bond_index)->z_angle;
	int bmult = terminal->bonds.at(bond_index)->multiplicity;

	// delete swaps
	terminal->bonds.erase(terminal->bonds.begin() + bond_index);
	group->subgroups.erase(group->subgroups.begin() + swap_index);

	// make bond
	Bond * b = allocateBond(terminal, e, xy_angle, z_angle, bmult);
}

void Anchor::attach(Anchor other)
{
	// delete swaps
	other.terminal->bonds.erase(other.terminal->bonds.begin() + other.bond_index);
	other.group->subgroups.erase(other.group->subgroups.begin() + other.swap_index);

	bond(other.terminal);

	// add sub to base
	group->subgroups.push_back(other.group);

}

void Anchor::attach(Element * e) { bond(e); group->subgroups.push_back(e); }

Anchor makeAnchor(Group * g, Element * e, Bond * b)
{
	int si, bi;
	Element * swap = b->next;
	for (int i = 0; i < (int)g->subgroups.size(); i++)
	{
		if (g->subgroups.at(i) == swap)
		{
			si = i;
			break;
		}
	}
	for (int i = 0; i < (int)e->bonds.size(); i++)
	{
		if (e->bonds.at(i) == b
			&& e->bonds.at(i)->xy_angle == b->xy_angle
			&& e->bonds.at(i)->z_angle == b->z_angle)
		{
			bi = i;
			break;
		}
	}

	return *new Anchor(g, e, bi, si);
}

Anchor makeDoubleAnchor(Group * g, Element * e, Bond * b1, Bond * b2)
{
	// delete secondary swap
	for (int i = 0; i < (int)g->subgroups.size(); i++)
	{
		if (g->subgroups.at(i) == b2->next)
		{
			g->subgroups.erase(g->subgroups.begin() + i);
			break;
		}
	}
	// delete second bond and adjust angles
	double z[3] = {60, 60, 180};
	double xy[3] = {0, 180, 0};
	int adjc = 0;
	bool n = (b1 == b2);
	for (int i = 0; i < (int)e->bonds.size(); i++)
	{
		if (e->bonds.at(i) == b2)
		{
			e->bonds.erase(e->bonds.begin() + i);
			i--;
		}
		else if (e->bonds.at(i)->next != e)
		{
			e->bonds.at(i)->xy_angle = xy[adjc];
			e->bonds.at(i)->z_angle = z[adjc];
			adjc++;
		}
	}
	if (n)
		b1 = assignSwapHydrogen(e);
	return makeAnchor(g, e, b1);
}
