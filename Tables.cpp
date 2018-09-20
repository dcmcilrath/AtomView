/*
	File:		Tables.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		Electronegativity
		Atomic Radius
		Drawing Color
*/

#include "AVHeaders.hpp"

double EN_TABLE[103] =
{
//1A	2A	3B	4B	5B	6B	7B	---------8B--------	1B	2B	3A	4A	5A	6A	7A	8A
2.2,																	-1,
.98,	1.57,											2.04,	2.55,	3.04,	3.44,	3.98,	-1,
.93,	1.31,											1.61,	1.90,	2.19,	2.58,	3.16,	-1,
.82,	1.00,	1.36,	1.54,	1.63,	1.66,	1.55,	1.83,	1.88,	1.91,	1.90,	1.65,	1.81,	2.01,	2.18,	2.55,	2.96,	3,
.82,	.95,	1.22,	1.33,	1.6,	2.16,	1.9,	2.2,	2.28,	2.2,	1.93,	1.69,	1.78,	1.96,	2.05,	2.1,	2.66,	2.6,
.79,	.98,	1.1,
/* Lanthanides */	1.12,	1.13,	1.14,	1.13,	1.17,	1.2,	1.2,	1.1,	1.22,	1.23,	1.24,	1.25,	1.1,	1.27,
/* Resume */		1.3,	1.5,	2.36,	1.9,	2.2,	2.2,	2.28,	2.54,	2,	1.62,	1.87,	2.02,	2.0,	2.2,	2.2,
.7,	.9,	1.1,
/* Actinides */		1.3,	1.5,	1.38,	1.36,	1.28,	1.13,	1.28,	1.3, 	1.3,	1.3,	1.3,	1.3,	1.3,	1.3
};

double AR_TABLE[54] =
{
//1A	2A	3B	4B	5B	6B	7B	---------8B--------	1B	2B	3A	4A	5A	6A	7A	8A
.18,																	.18,
.26,	.26,											.26,	.25,	.24,	.24,	.22,	.2,
.29,	.29,											.28,	.28,	.27,	.27,	.26,	.25,
.41,	.41,	.4,	.4,	.4,	.4,	.4,	.4,	.4,	.4,	.4,	.4,	.4,	.4,	.39,	.38,	.3,	3,
.82,	.95,	1.22,	1.33,	1.6,	2.16,	1.9,	2.2,	2.28,	2.2,	1.93,	1.69,	1.78,	1.96,	2.05,	2.1,	.33,	2.6,
/*.79,	.98,	1.1,
/* Lanthanides 	1.12,	1.13,	1.14,	1.13,	1.17,	1.2,	1.2,	1.1,	1.22,	1.23,	1.24,	1.25,	1.1,	1.27,
/* Resume 		1.3,	1.5,	2.36,	1.9,	2.2,	2.2,	2.28,	2.54,	2,	1.62,	1.87,	2.02,	2.0,	2.2,	2.2,
.7,	.9,	1.1,
/* Actinides 		1.3,	1.5,	1.38,	1.36,	1.28,	1.13,	1.28,	1.3, 	1.3,	1.3,	1.3,	1.3,	1.3,	1.3
*/};


double enegativity(int protons)
{
	if (protons > 103)
		return -1; // signifies undefined electronegativity
	else
		return EN_TABLE[protons-1];
}

double atomicRadius(int protons)
{
	if (protons > 54)
		return -1; // signifies undefined atomic radius
	else
		return AR_TABLE[protons-1];
}

Color getElementColor(int protons)
{
	switch (protons)
	{
	case  1: return *new Color(1, 1, 1); break;	//     Hydrogen: white
	case  5: return *new Color(1, .8, .8); break;	//        Boron: pink
	case  6: return *new Color(.3, .3, .3); break;	//       Carbon: black
	case  7: return *new Color(0, 0, 1); break;	//     Nitrogen: blue
	case  8: return *new Color(1, 0, 0); break;	//       Oxygen: red
	case  9: return *new Color(.8, 1, 0); break;	//     Fluorine: greenish-yellow
	case 15: return *new Color(1, .8, 0); break;	//   Phosphorus: darker yellow
	case 16: return *new Color(.8, .8, 0); break;	//       Sulfur: lighter yellow
	case 17: return *new Color(0, 1, 0); break;	//     Chlorine: green
	case 34: return *new Color(.6, .2, 0); break;	//     Selenium: brown
	case 35: return *new Color(.5, 0, 0); break;	//      Bromine: maroon
	case 53: return *new Color(1, 0, 1); break;	//       Iodine: purple
	default:
		if (	protons == 2 ||
			protons == 10 ||
			protons == 18 ||
			protons == 36 ||
			protons == 54 ||
			protons == 86)
		{
			return *new Color(0, 1, 1);	// Noble Gasses: cyan
		}
		else
			return *new Color(.7, .7, .7);	//       Metals: light grey
	}
}
