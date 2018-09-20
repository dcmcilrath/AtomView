/*
	File:		Main.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		November 2013
	Contents:
		Program Start/End
		Main update loop
			Calls to subprocesses
			Error Handling/Reporting
*/

#include "AVHeaders.hpp"

#define RENDER setUpRendering(0, 0, 0, *new Triple(1, 0, 0));

Display				* dpy;
Window				root;
GLint				att[] = { GLX_RGBA,
					  GLX_DEPTH_SIZE,
					  24,
					  GLX_DOUBLEBUFFER,
					  None };
XVisualInfo			* vi;
Colormap			cmap;
XSetWindowAttributes		swa;
Window 				win;
GLXContext			glc;
XWindowAttributes 		gwa;
XEvent				xev;

std::stringstream DEBUG;
bool DEBUG_ACTIVE = false;
double RESOLUTION = 5;
double DISTRIBUTION = 0.7;
bool END = false;

int main(int argc, char * argv[])
{
	/*
	 *	Initialization
	 */

	std::string param;
	std::string name;
	std::string dispname = "";
	std::string display;
	std::string form;
	bool dispform = false;
	std::vector<Token> * tokens;

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			param = (std::string)argv[i];

			if (param[0] == '-')
			{
				if (param == "--debug" || param == "-d")
					DEBUG_ACTIVE = true;
				else if ((param == "-r" || param == "--resolution") && i < argc - 1)
				{
					RESOLUTION = atof(argv[i+1]);
					i++;
				}
				else if (param == "--distribution" && i < argc - 1)
				{
					DISTRIBUTION = atof(argv[i+1]);
					i++;
				}
				else if (param == "-c" || param == "--common" && i < argc - 1)
				{
					dispname = std::string(argv[i+1]);
					i++;
				}
				else if (param == "-f" || param == "--form" && i < argc - 1)
				{
					param = std::string(argv[i+1]);
					if (param == "on" || param == "ON")
						dispform = true;
					i++;
				}
			}
			else
				name += " " + param;
		}
	}

	if (name == "")
	{
		printf("Usage: ./atom-view <IUPAC name> [-Option]\n");
		printf("Options:\n");
		printf("\t-c --common [name]\t\tSet display name to different common name\n");
		printf("\t-d --debug\t\t\tDisplay debugging information\n");
		printf("\t-f --form [on/off]\t\tToggle display of molecular formula (default: off)\n");
		printf("\t   --distribution [val]\t\tSet distribution variable\n");
		printf("\t-r --resolution [val]\t\tSet resolution variable\n");
		return 1;
	}

	try
	{
		Anchor a = generateMolecule(lex(name));
		a.group->RENDER;
		form = determineFormula(a.group);
		if (dispname == "")
			dispname = name;
	}
	catch (std::string emsg)
	{
		printf("Error: %s\n", emsg.c_str());
		return 1;
	}

	//Group * benzene = makeBenzene();
	//benzene->setUpRendering(0, 0, 0, *new Triple(sin(radians(34.2)), 0, cos(radians(34.2))));

	/*Group * sulforaphane = makeSulfoxide();
	Element * e = (Element *)sulforaphane->subgroups.at(0);
	makeAlkylGroup(1, makeAnchor(sulforaphane, e, assignSwapHydrogen(e)));
	Group * butane = makeAlkane(4);
	Element * e2 = getCarbonByPosition(butane, 4);
	Anchor a = makeAnchor(butane, e2, assignSwapHydrogen(e2, 3));
	a.attach(allocateElement(7));
	e2 = (Element *)butane->subgroups.at(butane->subgroups.size() - 1);
	e2 = addAtom(6, butane, e2, 0, 0, 2);
	e2 = addAtom(15, butane, e2, 0, 0, 2);
	//makeIsothiocyanate(makeAnchor(butane, e2, assignSwapHydrogen(e2)));
	e2 = getCarbonByPosition(butane, 1);
	a = makeAnchor(sulforaphane, e, assignSwapHydrogen(e));
	a.attach(makeAnchor(butane, e2, assignSwapHydrogen(e2)));
	sulforaphane->RENDER;

	name = "sulforaphane";
	form = determineFormula(sulforaphane);*/

	/*
 	 *	Graphical Setup 
 	 */
	
	dpy = XOpenDisplay(NULL);

	if (dpy == NULL)
		std::cout << "Fatal Error: Cannot connect to X server" << std::endl;

	root = DefaultRootWindow(dpy);
	vi = glXChooseVisual(dpy, 0, att);

	if (vi == NULL)
		std::cout << "Fatal Error: No appropriate visual info found" << std::endl;

	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;
	win = XCreateWindow(dpy, 
						root, 
						0, 
						0, 
						600, 
						600, 0,
						vi->depth, 
						InputOutput, 
						vi->visual,
						CWColormap | CWEventMask,
						&swa);
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "AtomView");
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
	glEnable(GL_DEPTH_TEST);
	glutInit(&argc, argv);

	/*
	 *	Event Loop
	 */

Element * e;

	while (!END)
	{
		// clear screen to white
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draws everything in the drawing objects vector
		drawAllObjects();

		//display name and formula in top corner
		display = dispname;
		if (dispform)
			display += " (" + form + ") ";
		drawString(display, -.9, .9, *new Color(0, 0, 0), dpy, win);

		//display center atom
		/*e = getTopObject(0, 0);
		std::cout << "Az of center = " << e->z << "\n";*/

		// handle user keypresses
		displayModeUI(dpy, xev);

		// make this buffer current
		glXSwapBuffers(dpy, win);

		if (DEBUG_ACTIVE)
		{
			printf("%s", DEBUG.str().c_str());
			DEBUG.str("");
		}
	}
	XCloseDisplay(dpy);
	return 0;
}
