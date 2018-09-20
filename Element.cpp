/*
	File:		Element.cpp
	Project:	AtomView
	Author:		Douglas C. McIlrath
	Date:		January 2014
	Contents:
		Element class storage
		Element class allocation functions
		Element class functions
*/

#include "AVHeaders.hpp"

// storage
Element element_data_bank[2048];
int e_next = 0;

// allocation
Element * allocateElement(int atomic_number, std::string name)
{
	element_data_bank[e_next].z = atomic_number;
	element_data_bank[e_next].name = name;
	e_next++;
	return &element_data_bank[e_next - 1];
}
Element * allocateElement(int z) { return allocateElement(z, ""); }
Element * allocateElement() { return allocateElement(1, ""); }

// class functions

Element::Element() { z = 1; bonds.clear(); }

void Element::setUpRendering(double xc, double yc, double zc, Triple vin)
{
	double size, bondlength;
	double alpha, theta, phi;

	Triple va, va2, u, ref, k(0, 0, 1);

	Color color;

	DrawingObject::Type dot = DrawingObject::sphere;

	Bond * b;

	if (associated == NULL)
	{
		size = atomicRadius(z);
		color = getElementColor(z);
		associated = addDrawingObject(xc, yc, zc, size, color, dot, this);

		for (int i = 0; i < bonds.size(); i++)
		{
			b = bonds.at(i);
			if (b->next != NULL)
			{
				if (b->next->associated == NULL)
				{
					bondlength = (size + atomicRadius(b->next->z) * DISTRIBUTION);

						DEBUG << "Bonding to next atom (id=" << b->next->name << ")\n";
						DEBUG << "\tReference vector (Vref):\n";
						DEBUG << "\t\t" << vin.toPolarString() << "\n";

					// vin represents the reference vector
					ref = vin;
					// for simplicity, make the reference vector of length 1
					ref.a = 1;
					ref = ref.makeCartesian();
						DEBUG << "\tVref hat:\n";
						DEBUG << "\t\t" << ref.toCartString() << "\n";

					// set up va, again with length 1
					va.set(1, radians(b->xy_angle + b->rotation), radians(b->z_angle));
						DEBUG << "\tInitial Va:\n";
						DEBUG << "\t\t" << va.toPolarString() << "\n";
					va = va.makeCartesian();
						DEBUG << "\tVa hat:\n";
						DEBUG << "\t\t" << va.toCartString() << "\n";

					// get angle of rotation
					alpha = getAngle(k, ref);

					if (alpha != 0 && alpha != 180)
					{
						// get axis of rotation
						u = cross(k, ref, alpha);
						u = u.makePolar();
							DEBUG << "\tU hat:\n";
							DEBUG << "\t\t" << u.toPolarString() << "\n";
							DEBUG << "\tAlpha = " << alpha << "\n";
						// get trasformation angles
						theta = u.b;
						phi = u.c;
	
	
	
						// transform va to u->k system
							DEBUG << "\tTransforming to the u->k system\n";
						va.rotate('z', -theta);
							DEBUG << "\t\tVa hat rotated by -u theta:\n";
							DEBUG << "\t\t\t" << va.toCartString() << "\n";
						va.rotate('y', phi);
							DEBUG << "\t\trotated by u phi:\n";
							DEBUG << "\t\t\t" << va.toCartString() << "\n";
						// rotate by alpha in u->k system
							DEBUG << "\tPreform rotation around u (now k) by alpha\n";
						va.rotate('z', alpha);
							DEBUG << "\t\trotated by alpha:\n";
							DEBUG << "\t\t\t" << va.toCartString() << "\n";
						// transform back to "absolute" system
							DEBUG << "\tReturn to normal system by preforming inverse rotations\n";
						va.rotate('y', -phi);
							DEBUG << "\t\trotated by -u phi:\n";
							DEBUG << "\t\t\t" << va.toCartString() << "\n";
						va.rotate('z', theta);
							DEBUG << "\t\trotated by u theta:\n";
							DEBUG << "\t\t\t" << va.toCartString() << "\n";
					}	
						va2 = va.makePolar();
						// give va correct bondlength
							DEBUG << "\tNew Angles:\n";
							DEBUG << "\t\t" << va2.toPolarString() << "\n";

					va2.a = bondlength;
					va = va2.makeCartesian();
						DEBUG << "\tVa':\n";
						DEBUG << "\t\t" << va.toCartString() << "\n";

					b->next->setUpRendering(va.a + xc, va.b + yc, va.c + zc, va2);
				}
			}
		}
	}
}
