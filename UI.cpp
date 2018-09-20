/*
	File:		UI.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		User interface functions:
			displayModeUI
*/

#include "AVHeaders.hpp"

bool displaymode=false;

void displayModeUI(Display * dpy, XEvent xev)
{
	char axis = 'y';
	double degrees = 5;
	double magnitude = .01;
	double factor = 1.25;
	std::string key;

	if (!displaymode)
	{
		if (XPending(dpy))
		{
			XNextEvent(dpy, &xev);

			if (xev.type == KeyPress)
			{
				key = getKeyRaw(xev);
	
				if (key == "Up" || key == "Down" || key == "Left" || key == "Right")
					translateAllObjects(key[0] - 'A' + 'a', magnitude);
				else if (key == "F1")
					RESOLUTION--;
				else if (key == "F2")
					RESOLUTION++;
				else if (key == "F3")
					DISTRIBUTION += .1;
				else if (key == "F4")
					DISTRIBUTION -= .1;
				else if (key == "F5")
					displaymode=true;
				else
				{
					key = capture(xev, getKeyRaw(xev), "");
	
					if (	key == "X" || key == "x" || key == "Y" ||
						key == "y" || key == "Z" || key == "z"	)
					{
	
						if (key == "x" || key == "X")
							axis = 'x';
						if (key == "y" || key == "Y")
							axis = 'y';
						if (key == "z" || key == "Z")
							axis = 'z';
	
						if (key == "X" || key == "Y" || key == "Z")
							degrees = -5;
						else
							degrees = 5;
	
						rotateAllObjects(0, 0, degrees, axis);
					}
					else if (key == "+" || key == "-")
					{
						if (key == "-")
							factor = 1.0 / factor;
						zoomAllObjects(factor);
					}
				}
			}
		}
	}
	else
	{
		if (XPending(dpy))
		{
			XNextEvent(dpy, &xev);

			if (xev.type == KeyPress)
			{
				key = getKeyRaw(xev);
				if (key == "F5")
					displaymode=false;
			}

		}
		rotateAllObjects(0, 0, degrees, 'y');
	}
}
