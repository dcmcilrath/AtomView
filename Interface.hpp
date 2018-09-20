/*
	File:		Interface.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		Febuary 2014
	Contents:
		Interface related global function declarations
*/

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

/*
 * 	User interface for display/view mode
 * 	located in UI.cpp
 * 	takes display pointer and X event handling objects
 * 	handles user commands to rotate (in future also zooming and shifting)
 */
void displayModeUI(Display *, XEvent);
/*
 *	checkKey
 *	located in Keys.cpp
 *	takes Xevent and keystring, returns true if pressed
 */
bool checkKey(XEvent, std::string);
/*
 *	getKeyRaw
 *	located in Keys.cpp
 *	takes Xevent, returns raw key value
 */
std::string getKeyRaw(XEvent);
/*
 *	capture
 *	located in Keys.cpp
 *	takes Xevent, raw key string and a string, preforms modifications on string based on keypress
 *		i.e. most keys append letter, but backspace will delete letter
 *		useful for text fields
 */
std::string capture(XEvent, std::string, std::string);

#endif
