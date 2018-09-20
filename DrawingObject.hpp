/*
	File:		DrawingObject.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		December 2013
	Contents:
		DrawingObject class definition
*/

#ifndef DRAWING_OBJECT_HPP
#define DRAWING_OBJECT_HPP

class DrawingObject
{
public:
	enum Type
	{
		invisible,
		sphere
	};


	double X;
	double Y;
	double Z;
	double size;
	Color color;
	Type type;
	Element * reference;				// pointer to source element

	DrawingObject();
	DrawingObject(double, double, double, double, Color, Type, Element *);

	void draw();
	void rotate(double, double, double, char);	// Takes 2d coordinates, degree measure, and char of axis to drop
							// 	rotates object around the given point
	void zoom(double);				// Takes a scalar, moves that much closer to center while simultaneously reducing size
};

extern std::vector<DrawingObject> full_object_list; 	// storage of all current drawing objects

//Allocation functions: take same arguments as constructors
DrawingObject * addDrawingObject(DrawingObject); 
DrawingObject * addDrawingObject();
DrawingObject * addDrawingObject(double, double, double, double, Color, DrawingObject::Type, Element *); 

//Rendering functions

void drawAllObjects();					// calls draw() on every object in full_object_list
void rotateAllObjects(double, double, double, char);	// calls rotate() on every object in full_object_list
void translateAllObjects(char, double);			// shifts all objects by specified amount, char = 'u/d/l/r' (up/down/left/right)
void zoomAllObjects(double);				// calls zoom() on every object in full_object_list

//Interface functions
Element * getTopObject(double, double);

#endif
