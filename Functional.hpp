/*
	File:		Functional.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		references to functions in Functional
*/

#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP

// Helping Functions
/*
 *	addAtom
 *	connects an atom
 */
Element * addAtom(int, Group *, Element *, double, double, int);
/*
 *	getCarbonByPosition
 *	iterates along chain and gets nth carbon atom
 */
Element * getCarbonByPosition(Group *, int);
/*
 *	assignSwapHydrogen
 *	returns the Bond to a hydrogen from the specified element, or null if element has no hydrogens
 *	the integer following is optional, but denotes to take the 2nd (or potentially 3rd) hydrogen
 */
Bond * assignSwapHydrogen(Element *, int);
Bond * assignSwapHydrogen(Element *);



// Chains

/*
 *	makeAlkane
 *	create a chain of carbons of arbitrary length
 */
Group * makeAlkane(int);
/*
 *	addBond
 *	deletes two hydrogens and adjusts bond angles
 *	also takes boolean: ==cis
 */
void addBond(Group *, Element *, bool);
/*
 * 	makeAlkylGroup
 * 	calls make Alkane to generate chain, then sets up anchor
 */
void makeAlkylGroup(int, Anchor);
/*
 *	makeVinylGroup
 *	R-CH=CH2
 */
void makeVinylGroup(Anchor);
/*
 *	makeAllylGroup
 *	R-CH2-CH=CH2
 */
void makeAllylGroup(Anchor);

// Rings
/*
 *	makeCycloAlkane
 *	create an arbitrary cyclo alkane
 */
//Group * makeCycloAlkane(int);
/*
 *	makeBenzene
 *	create benzene
 */
Group * makeBenzene();
/*
 *	makePhenylGroup
 *	R-benzene
 */
void makePhenylGroup(Anchor);
/*
 *	makeBenzylGroup
 *	R-CH3-benzene
 */
void makeBenzylGroup(Anchor);

// Oxygen-based
/*
 *	makeEther
 *	essentially makes H2O
 */
Group * makeEther();
/*
 *	makeHydroxylGroup
 *	R-OH
 */
void makeHydroxylGroup(Anchor);
/*
 *	makeKetone
 *	assumes Anchor group is a hydrocarbon and terminal has at least two hydrogens
 *	R=O
 */
void makeKetone(Anchor);
/*
 *	makeCarboxylGroup
 *	R-COOH
 */
void makeCarboxylGroup(Anchor);
/*
 *	makeAlkoxyGroup
 *	R-O-CnH(2n+1)
 */
void makeAlkoxyGroup(int, Anchor);
/*
 *	makeBenzoicAcid
 *	calls makeBenzene, adds methanoic acid
 */
Group * makeBenzoicAcid();
/*
 *	makeAcetoxyGroup
 *	R-O-(C=O)-CH3
 */
void makeAcetoxyGroup(Anchor);

// Nitrogen-based

/*
 *	makeImine
 *	creates NH2 base
 */
Group * makeImine();
/*
 *	makeImineGroup
 *	R=NH
 */
void makeIminoGroup(Anchor);
/*
 *	makeAmine
 *	creates NH3 base
 */
Group * makeAmine();
/*
 *	makeAminoGroup
 *	R-NH2
 */
void makeAminoGroup(Anchor);
/*
 *	makeAmmonioGroup
 *	R-NH3+
 */
void makeAmmonioGroup(Anchor);

// Sulphur-based

/*
 *	makeSulfide
 *	creats H2S base
 */
Group * makeSulfide();
/*
 *	makeThiolGroup
 *	R-SH
 */
void makeThiolGroup(Anchor);
/*
 *	makeSulfoxide
 *	creates H-(S=O)-H base
 */
Group * makeSulfoxide();
/*
 *	makeSulfinicAcid
 *	R-SOOH
 */
void makeSulfinicAcid(Anchor);
/*
 *	makeSulfone
 *	creates H-(O=S=0)-H base
 */
Group * makeSulfone();
/*
 *	makeSulfonicAcid
 *	R-SOOOH
 */
void makeSulfonicAcid(Anchor);

// Phosphorous-based

/*
 *	makePhosphane
 *	create PH3 base using makeAmine
 */
Group * makePhosphane();

// Halogens
/*
 *	makeHallogenicAcid
 *	takes atomic number of desired hallogen
 *	creates Hallogen-H base
 */
Group * makeHalogenicAcid(int);
/*
 *	hallogenate
 *	takes atomic number of desired hallogen
 *	R-hallogen
 */
void halogenate(int, Anchor);


#endif
