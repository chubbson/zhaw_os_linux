#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "shape.h"
#include "circle.h"
#include "triangle.h"
#include "square.h"

void usage(char *argv0, char *text) {
  printf("%s\n", text);
  printf("\n\nUsage:\n\n%s F A B N ID\n\n", argv0);
  printf("calculates integral of F from A to B of F() with N steps\n");
  printf("F must be one of sin cos tan cot sec csc exp log sqr cub\n");
  exit(1);
}

#define PI 3.14159265358979323846


// Shape function
double shape_area(shape const *s)
{
	return s->vptr->area(s);
}

double shape_cercumference(shape const *s)
{
	return s->vptr->circumference(s);
}

void shape_print(shape const *s)
{
	printf("shape - A: %f U: %f -> ", shape_area(s), shape_cercumference(s));
	s->vptr->print(s);
}

shape_vtbl the_shape_vtbl = {
	shape_area,
	shape_cercumference,
	shape_print
};


// Circle functions
double circle_area(circle const *c){
	return PI * c->radius * c->radius;
}

double circle_cercumference(circle const *c){
	return 2*PI * c->radius;
}

void circle_print(circle const *c){
	printf("circle - r: %f\n", c->radius);
}

typedef struct circle_vtbl circle_vtbl;
struct circle_vtbl {
	double (*area)(circle const *);
	double (*cercumference)(circle const *);
	void (*print)(circle const *);
};

static circle_vtbl the_circle_vtbl = {
	circle_area, 
	circle_cercumference,
	circle_print
};

void circle_construct(circle *c, double r){
	shape_construct(&c->base);
	c->base.vptr = (shape_vtbl *)&the_circle_vtbl;
	c->radius = r;
}

// square functions
double square_area(square const *s){
	return s->sidea * s->sidea;
}

double square_cercumference(square const *s){
	return 4*s->sidea;
}

void square_print(square const *s){
	printf("square - a: %f\n", s->sidea);
}

typedef struct square_vtbl square_vtbl;
struct square_vtbl {
	double (*area)(square const *);
	double (*cercumference)(square const *);
	void (*print)(square const *);
};

static square_vtbl the_square_vtbl = {
	square_area, 
	square_cercumference,
	square_print
};

void square_construct(square *s, double a){
	shape_construct(&s->base);
	s->base.vptr = (shape_vtbl *)&the_square_vtbl;
	s->sidea = a;
}

// triangle functions
double triangle_area(triangle const *t){
	double s = ((t->sidea)+(t->sideb)+(t->sidec))/2;
	return sqrt(s*(s-t->sidea)*(s-t->sideb)*(s-t->sidec));
}

double triangle_cercumference(triangle const *t){
	return t->sidea + t->sideb + t->sidec;
}

void triangle_print(triangle const *t){
	printf("triangle - a: %f b: %f c: %f\n", t->sidea, t->sideb, t->sidec);
}

typedef struct triangle_vtbl triangle_vtbl;
struct triangle_vtbl {
	double (*area)(triangle const *);
	double (*cercumference)(triangle const *);
	void (*print)(triangle const *);
};

static triangle_vtbl the_triangle_vtbl = {
	triangle_area, 
	triangle_cercumference,
	triangle_print
};

void triangle_construct(triangle *t, double a, double b, double c){
	shape_construct(&t->base);
	t->base.vptr = (shape_vtbl *)&the_triangle_vtbl;
	t->sidea = a;
	t->sideb = b;
	t->sidec = c;
}

// rectangle funcgtions


int main(int argc, char const *argv[])
{
	printf("%s\n", "trest");

	//circle c;

  	//struct circle *c = malloc(sizeof(struct circle));
  	//c = calloc(1, sizeof(struct circle));

	circle c1;
	circle c2;
	square s1;
	triangle t1;
	circle_construct(&c1,3);
	circle_construct(&c2,4);
	square_construct(&s1,5);
	triangle_construct(&t1,2,3,4);
	//double ar = shape_area((shape *)&c1);
	//double circum = circle_cercumference(&c1);

    circle_print(&c1);
    shape_print((shape *)&c1);
    shape_print((shape *)&t1);
    shape_print((shape *)&s1);
	printf("Circle: r: %f A: %f U: %f\n", c1.radius, circle_area(&c1), circle_cercumference(&c1));// c[0].radius);
	printf("Circle: r: %f A: %f U: %f\n", c2.radius, circle_area(&c2), circle_cercumference(&c2));// c[0].radius);

	//free(c);

	return 0;
}
/*
struct int_data {
  fun function;
  double a;
  double b;
  int n;
};

struct 

double cot(double x) {
  return cos(x)/sin(x);
}

void create_triangle(int a, int b, int ) {


}

void create_square(int a) {

}

void create_circule(int r) {

}

double area(struct shape *shape) {}
double circumference(struct shape *shape) {}
double simpson(struct int_data *data) {
	*/