/*
	File:		Headers.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		November 2013
	Contents:
		C/C++ Libraries used by program
		OpenGL Libraries used by program
		Class Listing
		Internal program header files
		Global functions
		Global variables
*/

#ifndef AVHEADERS_HPP
#define AVHEADERS_HPP

// C/C++ Libraries
#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>

// OpenGL Libraries
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glut.h>
	
//Class Listing
class Group;
class Element;
class Bond;
class Color;
class DrawingObject;
class Token;
class Triple;
class Anchor;

// Internal program header files
// Class definition headers
#include "Group.hpp"
#include "Element.hpp"
#include "Bond.hpp"
#include "Color.hpp"
#include "DrawingObject.hpp"
#include "Token.hpp"
#include "Triple.hpp"
#include "Anchor.hpp"

// Header files for global functions
#include "Functional.hpp"
#include "Trig.hpp"
#include "Interface.hpp"
#include "Tables.hpp"

// Global Functions
/*
 *	drawSphere
 *	located in DrawingTools.cpp
 *	takes coordinates (x, y, z), a radius, and a Color (see color.hpp) then draws a sphere
 */
void drawSphere(double, double, double, double, Color);
/*
 *	drawString
 *	located in Text.cpp
 *	draw a text string
 */
void drawString(std::string, double, double, Color, Display *, Window);
/*
 *	lex
 *	located in Lexer.lex
 *	takes an IUPAC name and generates tokens
 */
std::vector<Token> * lex(std::string);
/*
 *	generateMolecule
 *	located in Generate.cpp
 *	takes a vector of tokes and sets up molecular structure
 *	returns an anchor for nesting purposes
 */
Anchor generateMolecule(std::vector<Token> *);


//Global Variables
/*
 *	DEBUG
 *	Debuggin output steam, this is dumped to the console on every update cycle
 */
extern std::stringstream DEBUG;
/*
 *	RESOLUTION
 *	360/RESOLUTION = ring count in spheres
 */
extern double RESOLUTION;
/*
 *	DISTRIBUTION
 *	fraction of sphere radii used in bondlength
 */
extern double DISTRIBUTION;
/*
 *	END
 *	if true, exit event loop
 */
extern bool END;

#endif
