#ifndef CONFIG_H
#define CONFIG_H

#include "geo/vector.h"

typedef geo::point< 3, double > point;

struct obj
{
	double time;
	point pos;
	point vel;
};


#endif // CONFIG_H
