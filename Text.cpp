/* Text.cpp Utility File */

#include "AVHeaders.hpp"

void drawString(std::string text, double x, double y, Color color, Display *dpy, Window win)
{
	color.makeDrawingColor();
	glRasterPos2d(x, y);

	for (int i = 0; i < (int)text.size(); i++)
		//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
}
