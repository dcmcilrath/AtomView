/*
	File:		Functional.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		helper functions
		functions for creating structural groups:
			chains
			rings
			oxygen-based
			nitrogen-based
*/

#include "AVHeaders.hpp"

/*
 *	Helper Functions
 */

Element * addAtom(int z, Group * g, Element * prev, double xy_angle, double z_angle, int bondmult)
{
	Element * add = allocateElement(z);
	g->subgroups.push_back(add);
	Bond * b = allocateBond(prev, add, xy_angle, z_angle, bondmult);

	return add;
}

Element * getCarbonByPosition(Group * chain, int n)
{
	Element * current = (Element *)chain->subgroups.at(0);

	int b;

	for (int i = 1; i < n; i++)
	{
		for (b = 0; b < (int)current->bonds.size(); b++)
		{
			if (	current->bonds.at(b)->next->z == 6 &&
				current->bonds.at(b)->next != current)
			{
				current = current->bonds.at(b)->next;
				break;
			}
		}
		if (b >= (int)current->bonds.size())
		{
			// got stuck
			return NULL;
		}
	}

	return current;
}

Bond * assignSwapHydrogen(Element * e, int count, bool flip)
{
	int i = 0, f = 1;
	if (flip)
	{
		i = e->bonds.size()-1;
		f = -1;
	}

	for (; ((i >= 0 && flip) || (i < (int)e->bonds.size() && !flip)); i+=f)
	{
		if (e->bonds.at(i)->next->z == 1)
			count--;
		if (count == 0)
			return e->bonds.at(i);
	}
	// no available hydrogens
	return NULL;
}
Bond * assignSwapHydrogen(Element * e) { return assignSwapHydrogen(e, 1, true); } 
Bond * assignSwapHydrogen(Element * e, int c) { return assignSwapHydrogen(e, c, true); } 
Bond * assignSwapHydrogen(Element * e, bool f) { return assignSwapHydrogen(e, 1, f); } 


Anchor primaryAnchor(Group * g)
{
	Element * e = (Element *)g->subgroups.at(0);
	return makeAnchor(g, e, assignSwapHydrogen(e, false));
}

/*
 *	Chains
 */

Group * makeAlkane(int length)
{
	Group * chain = allocateGroup();
	Element * last, * current, * hydrogen;
	Bond * b;

	int flip = 1;

	// add first carbon
	current = allocateElement(6);
	chain->subgroups.push_back(current);

	// add first hydrogen (swap in case of alkyl group rather than alkane)
	hydrogen = addAtom(1, chain, current, 0, 180, 1);

	for (int i = 0; i < length; i++)
	{
		flip *= -1;
		// add hydrogens
		hydrogen = addAtom(1, chain, current, 90 + 30*flip, 70.5, 1);
		hydrogen = addAtom(1, chain, current, 270 - 30*flip, 70.5, 1);

		last = current;

		// add third bond (ususally carbon unless end of chain)
		if (i < length - 1)
			current = addAtom(6, chain, last, -90 * flip + 90, 70.5, 1);
		else
			hydrogen = addAtom(1, chain, last, -90 * flip + 90, 70.5, 1);
	}

	return chain;
}

void addBond(Group * chain, Element * position, bool cis)
{
	int hydrogen, del, cont;
	Bond * b;

	for (int c = 0; c < 2; c++)
	{
		del = -1; hydrogen = 0; cont = 0;

		// determine bonds
		for (int i = 1; i < (int)position->bonds.size(); i++)
		{
			if (position->bonds.at(i)->next != position && position->bonds.at(i)->next->z == 1 && hydrogen == 0)
			{
				if (del == -1)
					del = i;
				else
					hydrogen = i;
			}
			else if (position->bonds.at(i)->next != position)
				cont = i;
		}

		// adjust angles
		if (position->bonds.size() == 3)
		{
			b = position->bonds.at(cont);
			b->xy_angle = 0;
			b->z_angle = 0;
		}
		else if (position->bonds.size() == 4)
		{
			b = position->bonds.at(cont);
			b->z_angle = 60;
			if (c == 1 && !cis)
				b->xy_angle = 180;
			else
				b->xy_angle = 0;
			b = position->bonds.at(hydrogen);
			b->z_angle = 60;
			if (c == 1 && !cis)
				b->xy_angle = 0;
			else
				b->xy_angle = 180;
		}

		// delete one
		for (int i = 0; i < (int)chain->subgroups.size(); i++)
		{
			if (chain->subgroups.at(i) == position->bonds.at(del)->next)
			{
				chain->subgroups.erase(chain->subgroups.begin() + i);
				break;
			}
		}
		position->bonds.erase(position->bonds.begin() + del);

		// set position to other side of added bond
		if (del < cont)
			cont--;
		position = position->bonds.at(cont)->next;
	}
}

Anchor getAlkylAnchor(int length)
{
	Group * alkane = makeAlkane(length);
	Element * terminal = (Element *)alkane->subgroups.at(0);
	Bond * b = terminal->bonds.at(0);

	return makeAnchor(alkane, terminal, b);
}

void makeAlkylGroup(int length, Anchor base) { base.attach(getAlkylAnchor(length)); }

void allylvinyl(int n, Anchor base)
{
	Anchor a = getAlkylAnchor(n);
	addBond(a.group, getCarbonByPosition(a.group, n - 1), true);

	base.attach(a);
}

void makeVinylGroup(Anchor base) { allylvinyl(2, base); }
void makeAllylGroup(Anchor base) { allylvinyl(3, base); }

/*
 *	Rings
 */
Group * makeCycloAlkane(int size)
{
	// add cyclos code
}

Group * makeBenzene()
{
	Group * ring = allocateGroup();
	Element * current, * last, * hydrogen;

	last = allocateElement(6);
	ring->subgroups.push_back(last);
	hydrogen = addAtom(1, ring, last, 0, 180, 1);
	current = addAtom(6, ring, last, 180, 60, 2);
	current->name = "benzene ring carbon #1";

	for (int i = 0; i < 5; i++)
	{
		last = current;
		hydrogen = addAtom(1, ring, last, 180, 60, 1);
		current = addAtom(6, ring, last, 0, 60, 2);
		current->name = "benzene ring carbon #" + char(i + 2 + '0');
	}

	hydrogen = addAtom(1, ring, current, 180, 60, 1);

	return ring;
}

void makePhenylGroup(Anchor base)
{
	Group * benzene = makeBenzene();
	Element * carbon = (Element *)benzene->subgroups.at(0);
	base.attach(makeAnchor(benzene, carbon, assignSwapHydrogen(carbon)));
}

void makeBenzylGroup(Anchor base)
{
	Anchor in = getAlkylAnchor(1);
	base.attach(in);
	Anchor out = makeAnchor(in.group, in.terminal, assignSwapHydrogen(in.terminal));
	makePhenylGroup(out);
}

/*
 *	Oxygen-based
 */

Group * makeEther()
{
	Group * ether = allocateGroup();
	Element * hydrogen, * oxygen = allocateElement(8);
	ether->subgroups.push_back(oxygen);
	hydrogen = addAtom(1, ether, oxygen, 0, 180, 1);
	hydrogen = addAtom(1, ether, oxygen, 0, 70.5, 1);

	return ether;
}

void makeKetone(Anchor base)
{
	Anchor a = makeDoubleAnchor(base.group, base.terminal, assignSwapHydrogen(base.terminal), assignSwapHydrogen(base.terminal, 2));
	a.attach(allocateElement(8));
}

void makeHydroxylGroup(Anchor base)
{
	Group * oh = makeEther();
	Element * oxygen = (Element *)oh->subgroups.at(0);
	base.attach(makeAnchor(oh, oxygen, assignSwapHydrogen(oxygen, 2)));
}

void makeCarboxylGroup(Anchor base)
{
	makeHydroxylGroup(base);
	base = makeAnchor(base.group, base.terminal, assignSwapHydrogen(base.terminal));
	makeKetone(base);
}

Group * makeBenzoicAcid()
{
	Group * ring = makeBenzene();
	Element * carbon = (Element *)ring->subgroups.at(0);
	Anchor r = makeAnchor(ring, carbon, assignSwapHydrogen(carbon));
	Anchor a = getAlkylAnchor(1);
	r.attach(a);
	makeCarboxylGroup(makeAnchor(a.group, a.terminal, assignSwapHydrogen(a.terminal)));

	return ring;
}

void makeAlkoxyGroup(int length, Anchor base)
{
	Group * alkoxy = makeEther();
	Element * oxygen = (Element *)alkoxy->subgroups.at(0);
	Anchor a = makeAnchor(alkoxy, oxygen, assignSwapHydrogen(oxygen));
	makeAlkylGroup(length, a);
	a = makeAnchor(alkoxy, oxygen, assignSwapHydrogen(oxygen));
	base.attach(a);
}

void makeAcetoxyGroup(Anchor base)
{
	Anchor alkyl = getAlkylAnchor(2);


	Group * acetoxy = makeEther();
	Element * oxygen = (Element *)acetoxy->subgroups.at(0);
	Anchor a = makeAnchor(acetoxy, oxygen, assignSwapHydrogen(oxygen));
	a.attach(makeAnchor(alkyl.group, alkyl.terminal, assignSwapHydrogen(alkyl.terminal)));

	makeKetone(makeAnchor(alkyl.group, alkyl.terminal, assignSwapHydrogen(alkyl.terminal)));

	oxygen->bonds.at(1)->rotation = 90;

	base.attach(makeAnchor(acetoxy, oxygen, assignSwapHydrogen(oxygen)));
}

/*
 *	Nitrogen-based
 */
Group * makeImine()
{
	Group * imine = allocateGroup();
	Element * hydrogen, * nitrogen = allocateElement(7);
	imine->subgroups.push_back(nitrogen);
	hydrogen = addAtom(1, imine, nitrogen, 0, 180, 2);
	hydrogen = addAtom(1, imine, nitrogen, 0, 60, 1);

	return imine;
}
void makeIminoGroup(Anchor base)
{
	Anchor a = makeDoubleAnchor(base.group, base.terminal, assignSwapHydrogen(base.terminal), assignSwapHydrogen(base.terminal, 2));
	a.attach(primaryAnchor(makeImine()));
}

Group * makeAmine()
{
	Group * amine = allocateGroup();
	Element * hydrogen, * nitrogen = allocateElement(7);
	amine->subgroups.push_back(nitrogen);
	hydrogen = addAtom(1, amine, nitrogen, 0, 180, 1);
	hydrogen = addAtom(1, amine, nitrogen, 0, 70.5, 1);
	hydrogen = addAtom(1, amine, nitrogen, 120, 70.5, 1);

	return amine;
}
void makeAminoGroup(Anchor base) { base.attach(primaryAnchor(makeAmine())); }

void makeAmmonioGroup(Anchor base)
{
	Anchor a = primaryAnchor(makeAmine());
	Element * hydrogen = addAtom(1, a.group, a.terminal, 240, 70.5, 1);
	base.attach(a);
}

/*
 *	Sulfur-based
 */


Group * makeSulfide()
{
	Group * sulfide = makeEther();
	Element * sulfur = (Element *)sulfide->subgroups.at(0);
	sulfur->z = 16;

	return sulfide;
}
void makeThiolGroup(Anchor base) { base.attach(primaryAnchor(makeSulfide())); }

Group * makeSulfoxide()
{
	Group * sulfoxide = allocateGroup();
	Element * hydrogen, * oxygen, * sulfur = allocateElement(16);
	sulfoxide->subgroups.push_back(sulfur);
	hydrogen = addAtom(1, sulfoxide, sulfur, 0, 180, 1);
	hydrogen = addAtom(1, sulfoxide, sulfur, 0, 60, 1);
	oxygen = addAtom(8, sulfoxide, sulfur, 180, 60, 1);
	return sulfoxide;
}
void makeSulfinicAcid(Anchor base) { base.attach(primaryAnchor(makeSulfoxide())); }

Group * makeSulfone()
{
	Group * sulfoxide = allocateGroup();
	Element * hydrogen, * oxygen, * sulfur = allocateElement(16);
	sulfoxide->subgroups.push_back(sulfur);
	hydrogen = addAtom(1, sulfoxide, sulfur, 0, 180, 1);
	hydrogen = addAtom(1, sulfoxide, sulfur, 0, 70.5, 1);
	oxygen = addAtom(8, sulfoxide, sulfur, 120, 70.5, 1);
	oxygen = addAtom(8, sulfoxide, sulfur, 240, 70.5, 1);
	return sulfoxide;
}
void makeSulfonicAcid(Anchor base) { base.attach(primaryAnchor(makeSulfone())); }

/*
 *
 */

Group * makePhosphane()
{
	Group * phos = makeAmine();
	Element * p = (Element *)phos->subgroups.at(0);
	p->z = 15;
	return phos;
}

/*
 *	Halogens
 */
Group * makeHalogenicAcid(int z)
{
	Group * ha = allocateGroup();
	Element * hallogen = allocateElement(z);
	ha->subgroups.push_back(hallogen);
	Element * hydrogen = addAtom(1, ha, hallogen, 0, 180, 1);

	return ha;
}

void halogenate(int z, Anchor base) { base.attach(allocateElement(z)); }
