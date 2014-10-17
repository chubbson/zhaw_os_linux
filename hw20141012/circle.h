
#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "shape.h"

typedef struct circle circle;
struct circle {
	shape base;
	double radius;
};

void circle_construct(circle *c, double r);

#endif