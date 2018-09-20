/*
	File:		Lexer.lex
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		GNU Flex Lexer file for preforming lexical analysis on user input
*/

%{
#include "AVHeaders.hpp"

std::vector<Token> tokens;

int uncodePrefix(char *);

%}

DIGIT		[0-9]
CHAIN		meth|eth|prop|but|pent|hex|hept|oct|non|dec
CIRCLE		benzen(e)?|phen
SINGLE		ane|an
DOUBLE		ene|en
TRIPLE		yne|yn
BOND		{SINGLE}|{DOUBLE}|{TRIPLE}
ALIGNMENT	cis|trans
MULTIPLICITY	di|tri|tetra|penta|hexa|hepta
HALOGEN		fluor|chlor|brom|iod

MACRO		water|neopentane|"sulfuric acid"|lysine

%%

{DIGIT}+	{ tokens.push_back(*new Token(Token::number, atoi(yytext))); }
{MACRO}		{
			std::string name = (std::string)yytext;
			if (name == "water")
				name = "ether";
			else if (name == "sulfuric acid")
				name = "dihydroxysulfone";
			else if (name == "neopentane")
				name = "2,2-dimethylpropane";
			else if (name == "lysine")
				name = "2,6-diammoniohexanoic acid";

			std::vector<Token> * tmp = lex(name);
		}
{CHAIN}{BOND}?	{ tokens.push_back(*new Token(Token::chain, uncodePrefix(yytext))); }
{CIRCLE}	{ tokens.push_back(*new Token(Token::benzene)); }
"benzoic acid"	{ tokens.push_back(*new Token(Token::benzoic)); }
sulfide		{ tokens.push_back(*new Token(Token::sulfide)); }
sulfoxide	{ tokens.push_back(*new Token(Token::sulfoxide)); }
sulfone		{ tokens.push_back(*new Token(Token::sulfone)); }
ether		{ tokens.push_back(*new Token(Token::ether)); }
imine		{ tokens.push_back(*new Token(Token::imine)); }
amine		{ tokens.push_back(*new Token(Token::amine)); }
phosphane	{ tokens.push_back(*new Token(Token::phosphane)); }
{HALOGEN}ide	{
			int z = 0;
			switch (yytext[0])
			{
			case 'f': z = 9; break;
			case 'c': z = 17; break;
			case 'b': z = 35; break;
			case 'i': z = 53; break;
			}

			tokens.push_back(*new Token(Token::halogen, z));
		}
{BOND}		{
			int bond;
			switch (yytext[0])
			{
			case 'a': bond = 1; break;
			case 'e': bond = 2; break;
			case 'y': bond = 3; break;
			}
			tokens.push_back(*new Token(Token::bond, bond));
		}
{ALIGNMENT}	{ tokens.push_back(*new Token(Token::alignment, (std::string)yytext)); }
{MULTIPLICITY}	{
			int mult;
			switch (yytext[0])
			{
			case 'd': mult = 2; break;
			case 't':
				if (yytext[1] == 'r')
					mult = 3;
				else
					mult = 4;
				break;
			case 'p': mult = 5; break;
			case 'h':
				if (yytext[3] == 'x')
					mult = 6;
				else
					mult = 7;
				break;
			}
			tokens.push_back(*new Token(Token::multiplicity, mult));
		}
{CHAIN}yl	{ tokens.push_back(*new Token(Token::functional, uncodePrefix(yytext), "alkyl")); }
{CHAIN}oxy	{ tokens.push_back(*new Token(Token::functional, uncodePrefix(yytext), "alkoxy")); }
acetoxy		{ tokens.push_back(*new Token(Token::functional, "acetoxy")); }
vinyl		{ tokens.push_back(*new Token(Token::functional, "vinyl")); }
allyl		{ tokens.push_back(*new Token(Token::functional, "allyl")); }
ol|hydroxy	{ tokens.push_back(*new Token(Token::functional, "alcohol")); }
al|one		{ tokens.push_back(*new Token(Token::functional, "ketone")); }
"oic acid"|carboxy	{ tokens.push_back(*new Token(Token::functional, "carboxyl")); }
phenyl		{ tokens.push_back(*new Token(Token::functional, "phenyl")); }
benzyl		{ tokens.push_back(*new Token(Token::functional, "benzyl")); }
imino		{ tokens.push_back(*new Token(Token::functional, "imino")); }
amino		{ tokens.push_back(*new Token(Token::functional, "amino")); }
ammonio		{ tokens.push_back(*new Token(Token::functional, "ammonio")); }
thiol		{ tokens.push_back(*new Token(Token::functional, "thiol")); }
"sulfinic acid"	{ tokens.push_back(*new Token(Token::functional, "sulfinic")); }
"sulfonic acid"	{ tokens.push_back(*new Token(Token::functional, "sulfonic")); }

{HALOGEN}o	{
			int z = 0;
			switch (yytext[0])
			{
			case 'f': z = 9; break;
			case 'c': z = 17; break;
			case 'b': z = 35; break;
			case 'i': z = 53; break;
			}

			tokens.push_back(*new Token(Token::functional, z, "halogen"));
		}
"-"		{ }
","		{ tokens.push_back(*new Token(Token::comma)); }
"("		{ tokens.push_back(*new Token(Token::lparen)); }
")"		{ tokens.push_back(*new Token(Token::rparen)); }
" "		{ }
.		{ std::string emsg = "Unrecognized token: \"" + (std::string)yytext + "\""; throw emsg; }


%%

int uncodePrefix(char * str)
{
	int length = 0;
	switch (yytext[0])
	{
	case 'm': length = 1; break;
	case 'e': length = 2; break;
	case 'p':
		if (yytext[1] == 'r')
			length = 3;
		else	length = 5;
		break;
	case 'b': length = 4; break;
	case 'h':
		if (yytext[2] == 'x')
			length = 6;
		else	length = 7;
		break;
	case 'o': length = 8; break;
	case 'n': length = 9; break;
	case 'd': length = 10; break;
	}
	return length;
}

std::vector<Token> * lex(std::string str)
{
	tokens.clear();
	yy_scan_string(str.c_str());
	yylex();
	for (int i = 0; i < tokens.size(); i++)
		DEBUG << tokens.at(i).toString() << "\n";

	return &tokens;
}
