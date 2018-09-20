/*
	File:		DrawingObject.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		December 2013
	Contents:
		Storage for DrawingObjects
		DrawingObject allocation function
		Functions for the DrawingObject class
*/

#include "AVHeaders.hpp"

//storage for DrawingObjects
std::vector<DrawingObject> full_object_list;

//allocation
DrawingObject * addDrawingObject(DrawingObject dobj)
{
	full_object_list.push_back(dobj);
	return &full_object_list.back();
}

DrawingObject * addDrawingObject()
{
	return addDrawingObject(*new DrawingObject);
}
DrawingObject * addDrawingObject(double x, double y, double z, double s, Color c, DrawingObject::Type t, Element * e)
{
	return addDrawingObject(*new DrawingObject(x, y, z, s, c, t, e));
}


// rendering functions

void drawAllObjects()
{
	for (int i = 0; i < full_object_list.size(); i++)
		full_object_list.at(i).draw();
}

void rotateAllObjects(double p1, double p2, double degrees, char axis)
{
	for (int i = 0; i < full_object_list.size(); i++)
		full_object_list.at(i).rotate(p1, p2, degrees, axis);
}

void translateAllObjects(char dir, double magnitude)
{
	DrawingObject * d;
	for (int i = 0; i < full_object_list.size(); i++)
	{
		d = &full_object_list.at(i);
		switch (dir)
		{
		case 'u': d->Y += magnitude; break;
		case 'd': d->Y -= magnitude; break;
		case 'l': d->X -= magnitude; break;
		case 'r': d->X += magnitude; break;
		}
	}
}

void zoomAllObjects(double factor)
{
	for (int i = 0; i < full_object_list.size(); i++)
		full_object_list.at(i).zoom(factor);
}

// DrawingObject functions
DrawingObject::DrawingObject()
{
	X = 0;
	Y = 0;
	Z = 0;
	size = 0;
	color.set(0, 0, 0);
	type = invisible;
}

DrawingObject::DrawingObject(double x, double y, double z, double s, Color c, Type t, Element * e)
{
	X = x;
	Y = y;
	Z = z;
	size = s;
	color = c;
	type = t;
	reference = e;
}

void DrawingObject::draw()
{
	switch (type)
	{
	case sphere:
		drawSphere(X, Y, Z, size, color);
		break;
	}
}

void DrawingObject::rotate(double rot_x, double rot_y, double degrees, char axis)
{
	double * rel_x, * rel_y;
	if (axis == 'x' || axis == 'X')
	{
		rel_x = &Y;
		rel_y = &Z;
	}
	else if (axis == 'y' || axis == 'Y')
	{
		rel_x = &X;
		rel_y = &Z;
	}
	else
	{
		rel_x = &X;
		rel_y = &Y;
	}

	if (rot_x != *rel_x || rot_y != *rel_y)
	{
		double h = getDistance(*rel_x, *rel_y, rot_x, rot_y);
		double theta = getAngle(*rel_x, *rel_y, rot_x, rot_y);
		double phi = radians(degrees) + theta;
	
		*rel_x = rot_x + cos(phi) * h;
		*rel_y = rot_y + sin(phi) * h;
	}
}

void DrawingObject::zoom(double factor)
{
	size *= factor;
	X *= factor;
	Y *= factor;
	Z *= factor;
}

Element * getTopObject(double x, double y)
{
	Element * emax = NULL;
	double zmax;
	DrawingObject * dop;
	for (int i = 0; i < full_object_list.size(); i++)
	{
		dop = &full_object_list.at(i);
		if (getDistance(x, y, dop->X, dop->Y) <= dop->size)
		{
			if (emax == NULL || zmax < dop->Z)
			{
				emax = dop->reference;
				zmax = dop->Z;
			}
		}
	}

	return emax;
}
