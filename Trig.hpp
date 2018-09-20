/*
	File:		Trig.hpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		Febuary 2014
	Contents:
		Declarations of math global functions
*/

#ifndef TRIG_HPP
#define TRIG_HPP

/*
 *	radians
 *	located in Trig.cpp
 *	takes degrees, converts to radians
 */
double radians(double);
/*
 *	degrees
 *	located in Trig.cpp
 *	takes raidans, converts to degrees
 */
double degrees(double);
/*
 *	getDistance
 *	located in Trig.cpp
 *	takes two points (x1, y1, x2, y2)
 *	returns euclidian distance
 */
double getDistance(double, double, double, double);
/*
 *	getAngle
 *	located in Trig.cpp
 *	takes two points (x1, y1, x2, y2)
 *	assuming point 2, is relative origin, return standard position angle whose terminator
 *	passes through point 1
 */
double getAngle(double, double, double, double);

#endif
