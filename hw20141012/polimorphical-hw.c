#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "shape.h"
#include "circle.h"

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



int main(int argc, char const *argv[])
{
	printf("%s\n", "trest");

	//circle c;

  	//struct circle *c = malloc(sizeof(struct circle));
  	//c = calloc(1, sizeof(struct circle));

	circle c1;
	circle c2;
	circle_construct(&c1,3);
	circle_construct(&c2,4);
	double ar = shape_area((shape *)&c1);
	double circum = circle_cercumference(&c1);

    circle_print(&c1);
    shape_print((shape *)&c1);
	printf("Circle: r: %f A: %f U: %f\n", c1.radius, ar, circle_cercumference(&c1));// c[0].radius);
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