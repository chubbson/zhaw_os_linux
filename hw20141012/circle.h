
#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "shape.h"

typedef struct circle circle;
struct circle {
	shape base;
	double radius;
};

void circle_construct(circle *c, double r);
/*{
	shape_construct(&c->base);
	c->base.vptr = (shape_vtbl *)&the_circle_vtbl;
	c->radius = r;
}*/
/*
double circle_area(circle const *c);
double circle_cercumference(circle const *c);
*/
#endif