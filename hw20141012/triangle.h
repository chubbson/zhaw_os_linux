#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include "shape.h"

typedef struct triangle triangle;
struct trianlge {
	shape base;
	double vara;
	double varb;
	double varc;
};

void circle_construct(circle *c, double a, double b, double c);

#endif