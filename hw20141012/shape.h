
#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

typedef struct shape shape;

typedef struct shape_vtbl shape_vtbl;
struct shape_vtbl{
	double (*area)(shape const *s);
	double (*circumference)(shape const *s);
	void (*print)(shape const *s);
};

extern shape_vtbl the_shape_vtbl;

struct shape {  
	shape_vtbl *vptr;
};

inline
//void shape_construct(shape *s);
void shape_construct(shape *s) {
	s->vptr = &the_shape_vtbl;
}

double shape_area(shape const *s);
double shape_cercumference(shape const *s);
void shape_print(shape const *s);

#endif