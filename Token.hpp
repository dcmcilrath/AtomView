/*
	File:		Token.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		Token class which stores tokens from lexer
*/


#ifndef TOKEN_HPP
#define TOKEN_HPP

class Token
{
public:
	enum Type			// Token type
	{
		empty,
		chain,
		multiplicity,
		bond,
		ether,
		imine,
		amine,
		phosphane,
		sulfide,
		sulfoxide,
		sulfone,
		halogen,
		benzene,
		benzoic,
		alignment,
		functional,
		number,
		hyphen,
		comma,
		lparen,
		rparen,
	};

	/*enum Ftype
	{
		none,
		alkyl,
		vinyl,
		allyl,
		phenyl,
		benzyl,
		napthyl,
		indolyl,
		hydroxyl,
		aldehyde,
		carboxyl,
		alkoxy,
		acetoxy,
		amino,
		ammonio,
		nitro,
		halogenation,
	};*/

	Type type;
	std::string str;		// Associated text
	int count;			// In some cases, store numeric value instead

	/*
 	 *	Constructors
 	 */ 	

	Token() { type = empty; str = ""; count = 0; }
	Token(Type t) { type = t; str = ""; count = 0; }
	Token(Type t, int c) { type = t; count = c; str = ""; }
	Token(Type t, std::string s) { type = t; str = s; count = 0; }
	Token(Type t, int c, std::string s) { type = t; str = s; count = c; }

	/*
	 *	Convert to string for simple printing
	 */

	std::string toString()
	{
		std::stringstream ss;
		ss << "< ";
		switch (type)
		{
		case empty:        ss << "empty        "; break;
		case chain:        ss << "chain        " << count; break;
		case multiplicity: ss << "multiplicity " << count; break;
		case bond:         ss << "bonds        " << count; break;
		case alignment:    ss << "alignment    " << str; break;
		case functional:   ss << "functional   " << str; break;
		case number:       ss << "number       " << count; break;
		case hyphen:       ss << "hyphen "; break;
		case comma:        ss << "comma "; break;
		case lparen:       ss << "left paren "; break;
		case rparen:       ss << "right paren "; break;
		}

		ss << " >";

		return ss.str();
	}
};

#endif
