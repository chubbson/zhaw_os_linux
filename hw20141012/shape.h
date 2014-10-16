
#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

typedef struct shape shape;
typedef struct shape_vtbl shape_vtbl;

struct shape_vtbl{
	double (*area)(shape const *s);
	double (*circumference)(shape const *s);
};

struct shape {  
	shape_vtbl *vptr;
};

void shape_construct(shape *s);
double shape_area(shape const *s);
double shape_cercumference(shape const *s);

#endif