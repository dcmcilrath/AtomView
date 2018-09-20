/*
	File:		DrawingTools.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		December 2013
	Contents:
		Graphical tools functions:
			drawSphere
*/

#include "AVHeaders.hpp"

//Graphical tools functions
void drawSphere(double x, double y, double z, double r, Color color)
{
	double last_radius = 0;
	double current_radius;
	double shade;
	double delta_z;
	Color tmpcolor;
	for (double i = RESOLUTION+90; i <= 180; i += RESOLUTION)
	{
		shade = (1 - sin(radians(i))) * .9 + .1;

		tmpcolor = color;
		tmpcolor.scale(shade);
		tmpcolor.makeDrawingColor();

		current_radius = sin((i * M_PI) / 180) * r;
		delta_z = cos(radians(i)) * r;

		glBegin(GL_QUADS);
		for (double n = RESOLUTION; n <= 360; n += RESOLUTION)
		{
			glVertex3d(	x + cos(radians(n-RESOLUTION)) * last_radius, 
					y + sin(radians(n-RESOLUTION)) * last_radius,
					z + delta_z);
			glVertex3d(	x + cos(radians(n-RESOLUTION)) * current_radius,
					y + sin(radians(n-RESOLUTION)) * current_radius,
					z + delta_z);
			glVertex3d(	x + cos(radians(n)) * current_radius,
					y + sin(radians(n)) * current_radius,
					z + delta_z);
			glVertex3d(	x + cos(radians(n)) * last_radius,
					y + sin(radians(n)) * last_radius,
					z + delta_z);
		}
		glEnd();
		last_radius = current_radius;
	}
}
