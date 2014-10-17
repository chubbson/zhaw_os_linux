#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include "shape.h"

typedef struct square square;
struct circle {
	shape base;
	double side;
};

void square_construct(square *c, double a);

#endif