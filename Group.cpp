/*
	File:		Group.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		Group storage
		Group allocation
		Group class functions
		
*/

#include "AVHeaders.hpp"

// storage
Group group_data_bank[2048];
int g_next = 0;

// allocation
Group * allocateGroup() { g_next++; return &group_data_bank[g_next - 1]; }

// group class functions
Group::Group() { subgroups.clear(); }

int Group::configureGroup() { }

void Group::setUpRendering(double x, double y, double z, Triple src)
{
	Element * e;
	if (subgroups.at(0)->subgroups.size() > 0)
		subgroups.at(0)->setUpRendering(x, y, z, src);
	else
	{
		e = (Element *)subgroups.at(0);
		e->setUpRendering(x, y, z, src);
	}
}

int counts[118];

void updateCounts(Group * g)
{
	Element * e;
	for (int i = 0; i < (int)g->subgroups.size(); i++)
	{
		// if element
		if (g->subgroups.at(i)->subgroups.size() == 0)
		{
			e = (Element *)g->subgroups.at(i);
			counts[e->z - 1]++;
		}
		else
			updateCounts(g->subgroups.at(i));
	}
}

std::string determineFormula(Group * g)
{
	for (int i = 0; i < 118; i++)
		counts[i] = 0;
	updateCounts(g);

	int importants[10] = {5, 0, 6, 14, 15, 7, 8, 16, 34, 52};
	std::string assoc[10] = {"C", "H", "N", "P", "S", "O", "F", "Cl", "Br", "I"};
	std::stringstream ss;

	for (int i = 0; i < 8; i++)
	{
		if (counts[importants[i]] > 0)
		{
			ss << assoc[i];
			if (counts[importants[i]] > 1)
				ss << counts[importants[i]];
		}
	}

	return ss.str();
}
