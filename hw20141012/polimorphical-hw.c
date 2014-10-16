#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

void usage(char *argv0, char *text) {
  printf("%s\n", text);
  printf("\n\nUsage:\n\n%s F A B N ID\n\n", argv0);
  printf("calculates integral of F from A to B of F() with N steps\n");
  printf("F must be one of sin cos tan cot sec csc exp log sqr cub\n");
  exit(1);
}

#define PI 3.14159265358979323846

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

static shape_vtbl the_shape_vtbl = {
	shape_area,
	shape_cercumference
};

void shape_construct(shape *s) {
	s->vptr = &the_shape_vtbl;
}

typedef struct circle circle;
struct circle {
	shape base;
	double radius;
};

void circle_construct(circle *c, double r);

double circle_area(circle const *c)
{
	return PI * c->radius * c->radius;
}

double circle_cercumference(circle const *c){
	return 2*PI * c->radius;
}

typedef struct circle_vtbl circle_vtbl;
struct circle_vtbl {
	double (*area)(circle const *);
	double (*perimeter)(circle const *);
};

static circle_vtbl the_circle_vtbl = {
	circle_area, 
	circle_cercumference
};

void circle_construct(circle *c, double r){
	shape_construct(&c->base);
	c->base.vptr = (shape_vtbl *)&the_circle_vtbl;
	c->radius = r;
}


int main(int argc, char const *argv[])
{
	printf("%s\n", "trest");
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