/*
	File:		Keys.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		December 2013
	Contents:
		checkKey function
		capture function (for typing)
*/

#include <X11/X.h>
#include <X11/Xlib.h>
#include <string>
#include <iostream>

std::string capture(XEvent, std::string, std::string);

std::string getKeyRaw(XEvent xev)
{
	if (xev.type == KeyPress)
		return XKeysymToString(XLookupKeysym(&xev.xkey, 0));
	else
		return "empty";
}

bool checkKey(XEvent xev, std::string str)
{
	if (xev.type == KeyPress)
		if (str == capture(xev, getKeyRaw(xev), ""))
			return true;
	return false;

}

std::string capture(XEvent xev, std::string key_raw, std::string str)
{
	if (key_raw == "BackSpace" && str.size() > 0)
		str.resize(str.size()-1);
	else if (key_raw.size() == 1)
	{
		if (xev.xkey.state & ShiftMask)
		{
			if (key_raw[0] >= 'a' && key_raw[0] <= 'z')
				str += key_raw[0] + ('A' - 'a');
			else
			{
				switch (key_raw[0])
				{
				case '1': str += "!"; break;
				case '2': str += "@"; break;
				case '3': str += "#"; break;
				case '4': str += "$"; break;
				case '5': str += "%"; break;
				case '6': str += "^"; break;
				case '7': str += "&"; break;
				case '8': str += "*"; break;
				case '9': str += "("; break;
				case '0': str += ")"; break;
				}
			} 
		}
		else 
			str += key_raw;	
	}
	else
	{
		if (key_raw == "space")
			str += " ";
		else if (key_raw == "apostrophe")
		{
			if (xev.xkey.state & ShiftMask)
				str += "\"";
			else
				str += "'";
		}
		else if (key_raw == "comma")
		{
			if (xev.xkey.state & ShiftMask)
				str += "<";
			else
				str += ",";
		}
		else if (key_raw == "period")
		{
			if (xev.xkey.state & ShiftMask)
				str += ">";
			else
				str += ".";
		}
		else if (key_raw == "minus")
		{
			if (xev.xkey.state & ShiftMask)
				str += "_";
			else
				str += "-";
		}
		else if (key_raw == "equal")
		{
			if (xev.xkey.state & ShiftMask)
				str += "+";
			else
				str += "=";
		}
		else if (key_raw == "slash")
		{
			if (xev.xkey.state & ShiftMask)
				str += "?";
			else
				str += "/";
		}
		else if (key_raw == "backslash")
		{
			if (xev.xkey.state & ShiftMask)
				str += "|";
			else
				str += "\\";
		}
		else if (key_raw == "semicolon")
		{
			if (xev.xkey.state & ShiftMask)
				str += ":";
			else
				str += ";";
		}
		else if (key_raw == "bracketright")
		{
			if (xev.xkey.state & ShiftMask)
				str += "}";
			else
				str += "]";
		}
		else if (key_raw == "bracketleft")
		{
			if (xev.xkey.state & ShiftMask)
				str += "{";
			else
				str += "[";
		}
		else if (key_raw == "grave")
		{
			if (xev.xkey.state & ShiftMask)
				str += '~';
			else
				str += '`';
		}
	}
	return str;
}
