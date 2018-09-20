/*
	File:		Bond.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		December 2013
	Contents:
		Bond storage
		Bond allocation
		Bond constructor
*/

#include "AVHeaders.hpp"

// storage
Bond bond_data_bank[2048];
int b_next = 0;

// allocation
Bond * allocateBond() { b_next++; return &bond_data_bank[b_next - 1]; }

Bond * allocateBond(Element * ref, Element * nxt)
{
	bond_data_bank[b_next].reference = ref;
	ref->bonds.push_back(&bond_data_bank[b_next]);
	bond_data_bank[b_next].next = nxt;
	nxt->bonds.push_back(&bond_data_bank[b_next]);
	b_next++;
	return &bond_data_bank[b_next - 1];
}

Bond * allocateBond(Element * ref, Element * nxt, double xy, double z) { return allocateBond(ref, nxt, xy, z, 1); }

Bond * allocateBond(Element * ref, Element * nxt, double xy, double z, int mult)
{
	Bond * bp = allocateBond(ref, nxt);
	bp->xy_angle = xy;
	bp->z_angle = z;
	bp->multiplicity = mult;
	return bp;
}

// constructor
Bond::Bond()
{
	reference = NULL;
	next = NULL;
	xy_angle = 0;
	z_angle = 0;
	rotation = 0;
	multiplicity = 1;
}
