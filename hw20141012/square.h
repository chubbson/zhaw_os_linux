#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include "shape.h"

typedef struct square square;
struct square {
	shape base;
	double sidea;
};

void square_construct(square *s, double a);

#endif