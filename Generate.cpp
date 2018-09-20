/*
	File:		Generate.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		Febuary 2014
	Contents:
		generateMolecule function definition which turnes tokens into a structure
*/

#include "AVHeaders.hpp"

Anchor generateMolecule(std::vector<Token> * tokens)
{
	/*
 	 *	Algorithm overview:
 	 *	> Step 1: Iterate over molecule identifying
 	 *		nests (parenthesis), create substring
 	 *		base of molecule
 	 *		functional groups, append these to vector with matching location
 	 *	> Step 2: Build base of molecule
 	 *	> Step 3: Iterate over list of functional groups
 	 *		build any nests
 	 *		create an anchor based on location
 	 *		attach group
 	 */

	Group * molecule;
	Element * atom;
	Bond * b;
	Anchor a;
	Token * base, * functional;
	std::vector<int> locations;
	std::vector<Token> sublist;
	std::vector<std::vector<Token> > sublists;
	std::vector<Token *> functionals;

	std::string err;
	int searches, duplicates, plevel = 0;
	int nest_count = 0;
	int gap_start;

	// step 1:
	
	for (int i = 0; i < tokens->size(); i++)
	{
		if (tokens->at(i).type == Token::lparen)
		{
			plevel++;
			if (plevel == 1)
			{
				sublist.clear();
				gap_start = i;
			}
		}
		else if (tokens->at(i).type == Token::rparen)
		{
			plevel--;
			if (plevel == 0)
			{
				sublists.push_back(sublist);
				tokens->erase(tokens->begin() + gap_start, tokens->begin() + i + 1);
				i = gap_start;
				tokens->insert(tokens->begin() + i, *new Token(Token::functional, "nest"));
				i--; 
			}
		}
		else if (plevel > 0)
			sublist.push_back(tokens->at(i));
		else
		{
			if (	tokens->at(i).type == Token::chain ||
				tokens->at(i).type == Token::ether ||
				tokens->at(i).type == Token::amine ||
				tokens->at(i).type == Token::phosphane ||
				tokens->at(i).type == Token::imine ||
				tokens->at(i).type == Token::sulfide ||
				tokens->at(i).type == Token::sulfoxide ||
				tokens->at(i).type == Token::sulfone ||
				tokens->at(i).type == Token::halogen ||
				tokens->at(i).type == Token::benzene ||
				tokens->at(i).type == Token::benzoic ||
				i == tokens->size() - 1)
				base = &tokens->at(i);
			else if (tokens->at(i).type == Token::functional)
			{
				functional = &tokens->at(i);
				if (i > 0 && tokens->at(i-1).type == Token::multiplicity)
					searches = tokens->at(i-1).count;
				else
					searches = 1;
	
				duplicates = searches;
				// if available, find specified locations
				for (int n = i-1; (n >= 0 && searches > 0); n--)
				{
					if (tokens->at(n).type == Token::number)
					{
						locations.push_back(tokens->at(n).count);
						searches--;
					}
					else if (tokens->at(n).type != Token::comma && tokens->at(n).type != Token::multiplicity)
						break;
				}
	
				// else use defaults
				for (int n = searches; n > 0; n--)
				{
					if (functional->str == "alkyl")
						locations.push_back(functional->count + 1);
					else
						locations.push_back(1);
				}	
				for (int n = 0; n < duplicates; n++)
					functionals.push_back(functional);
			}
		}
	}

	// Step 2:

	switch (base->type)
	{
	case Token::chain: molecule = makeAlkane(base->count); break;
	case Token::benzene: molecule = makeBenzene(); break;
	case Token::benzoic: molecule = makeBenzoicAcid(); break;
	case Token::ether: molecule = makeEther(); break;
	case Token::imine: molecule = makeImine(); break;
	case Token::amine: molecule = makeAmine(); break;
	case Token::phosphane: molecule = makePhosphane(); break;
	case Token::sulfide: molecule = makeSulfide(); break;
	case Token::sulfoxide: molecule = makeSulfoxide(); break;
	case Token::sulfone: molecule = makeSulfone(); break;
	case Token::halogen: molecule = makeHalogenicAcid(base->count); break;
	}

	// Step 3:

	for (int i = 0; i < locations.size(); i++)
	{
		if (	base->type == Token::ether || base->type == Token::amine ||
			base->type == Token::sulfide || base->type == Token::sulfoxide ||
			base->type == Token::sulfone || base->type == Token::phosphane)
			atom = (Element *)molecule->subgroups.at(0);
		else
			atom = getCarbonByPosition(molecule, locations.at(i));

		if (atom == NULL)
		{
			err = "Location out of range";
			throw err;
		}

		b = assignSwapHydrogen(atom);
		if (b == NULL)
		{
			err = "Atom is out of bonds";
			throw err;
		}

		a = makeAnchor(molecule, atom, b);

		if (functionals.at(i)->str == "nest")
		{
			a.attach(generateMolecule(&sublists.at(nest_count)));
			nest_count++;
		}
		else if (functionals.at(i)->str == "alkyl")
			makeAlkylGroup(functionals.at(i)->count, a);
		else if (functionals.at(i)->str == "alkoxy")
			makeAlkoxyGroup(functionals.at(i)->count, a);
		else if (functionals.at(i)->str == "acetoxy")
			makeAcetoxyGroup(a);
		else if (functionals.at(i)->str == "vinyl")
			makeVinylGroup(a);
		else if (functionals.at(i)->str == "allyl")
			makeAllylGroup(a);
		else if (functionals.at(i)->str == "phenyl")
			makePhenylGroup(a);
		else if (functionals.at(i)->str == "benzyl")
			makeBenzylGroup(a);
		else if (functionals.at(i)->str == "alcohol")
			makeHydroxylGroup(a);
		else if (functionals.at(i)->str == "ketone")
			makeKetone(a);
		else if (functionals.at(i)->str == "carboxyl")
			makeCarboxylGroup(a);
		else if (functionals.at(i)->str == "imino")
			makeIminoGroup(a);
		else if (functionals.at(i)->str == "amino")
			makeAminoGroup(a);
		else if (functionals.at(i)->str == "ammonio")
			makeAmmonioGroup(a);
		else if (functionals.at(i)->str == "thiol")
			makeThiolGroup(a);
		else if (functionals.at(i)->str == "sulfinic")
			makeSulfinicAcid(a);
		else if (functionals.at(i)->str == "sulfonic")
			makeSulfonicAcid(a);
		else if (functionals.at(i)->str == "halogen")
			halogenate(functionals.at(i)->count, a);
	}

	atom = (Element *)molecule->subgroups.at(0);
	b = assignSwapHydrogen(atom);
	if (b != NULL)
		a = makeAnchor(molecule, atom, b);
	else
	{
		a.group = molecule;
		a.terminal = atom;
		a.swap_index = 0;
		a.bond_index = 0;
	}

	return a;
}
