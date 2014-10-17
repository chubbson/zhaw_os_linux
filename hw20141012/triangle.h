#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include "shape.h"

typedef struct triangle triangle;
struct triangle {
	shape base;
	double sidea;
	double sideb;
	double sidec;
};

void trianlge_construct(triangle *t, double a, double b, double c);

#endif