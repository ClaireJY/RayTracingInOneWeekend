#pragma once

#include "vec3.h"
#include <iostream>
#include <fstream>

void write_color(ofstream& out, color pixel_color)
{
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
}
