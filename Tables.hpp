/*
	File:		Tables.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		Febuary 2014
	Contents:
		Declarations of functions in Tables.cpp
*/

#ifndef TABLES_HPP
#define TABLES_HPP

// Tables
/*
 *	Enegativity
 *	located in Tables.cpp
 *	takes atomic number, returns element's electronegativity
 */
double enegativity(int);
/*
 *	Atomic Radius
 *	located in Tables.cpp
 *	takes atomic number
 *	returns the graphical base atomic radius (before zooming) of an element
 */
double atomicRadius(int);
/*
 * 	Get Element Color
 * 	located in Tables.cpp
 * 	takes atomic number, returns a Color used for drawing that element on screen
 */
Color getElementColor(int);

#endif
