/**
 * Author: David Hauri 
 * Thema: polimorph sample in c
 * gcc Sample: gcc polimorphical-hw.c -o polimorphical-hw -lm
 * HINT: DONT Miss the -lm directive!!
 */


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

// define PI
#define PI 3.14159265358979323846
#define ARRAYCNT 10


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
	double s = ((t->sidea)+(t->sideb)+(t->sidec))/2.0;
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
	while(isnan(triangle_area(t)))
		// choose new random number area could not be calculated
	{
		t->sidea = rand()%15;
		t->sideb = rand()%15;
		t->sidec = rand()%15;
	}
}

struct shapelink {
	shape *s;
	struct shapelink *next; 
};

void fill_shapellist(struct shapelink *sl, int ncount){
	switch(rand()%3)
	{
		case 0: 
			sl->s = malloc(sizeof(struct circle));
			circle_construct((struct circle *)sl->s, rand()%15);
		break;
		case 1:
			sl->s = malloc(sizeof(struct square));
			square_construct((struct square *)sl->s, rand()%15);
		break;
		case 2: 
			sl->s = malloc(sizeof(struct triangle));
			triangle_construct((struct triangle *)sl->s, rand()%15, rand()%15, rand()%15);
		break; 
	}
	ncount--;
	if(ncount > 0)
	{
		sl->next = malloc(sizeof(struct shapelink));
		fill_shapellist(sl->next, ncount); 
	}
	else
	{
		sl->next = 0;
		return;
	}

}

void free_shapellist(struct shapelink *sl){
	if(sl->next != 0)
	{
		free_shapellist(sl->next);
		free(sl->next);
		sl->next = 0; 
	}
	free(sl->s);
	sl->s = 0; 
}

void print_shapellist(struct shapelink *sl){
	shape_print(sl->s);
	if(sl->next != 0)
	{
		print_shapellist(sl->next);
	}
}

double shapellist_area(struct shapelink *sl, double akk) {
	if(sl->next != 0)
	{
		printf("%d - %d - %d\n", akk, shape_area(sl->s), shape_area(sl->s)+akk);
		return shapellist_area(sl->next, shape_area(sl->s)+akk);
	}
	return akk;
}

// Main method
int main(int argc, char const *argv[])
{
  	//struct circle *c = malloc(sizeof(struct circle));
  	//c = calloc(1, sizeof(struct circle));

	circle c1;
	square s1;
	triangle t1;
	circle_construct(&c1,3);
	square_construct(&s1,5);
	triangle_construct(&t1,2,3,4);
	//double ar = shape_area((shape *)&c1);
	//double circum = circle_cercumference(&c1);

    circle_print(&c1);
    shape_print((shape *)&c1);
    shape_print((shape *)&t1);
    shape_print((shape *)&s1);

    // allocate memory for an aray of circles
    struct circle *circles = calloc(ARRAYCNT, sizeof(struct circle));

	// seed random sequence
	srand(time(NULL));
    int i = 0;
    double sumar = 0; 
    for (i = 0; i < ARRAYCNT; ++i)
    {
    	//Create each circle
    	circle_construct((&circles[i]), rand()%15);
    	// print each circle
    	shape_print((shape *)&circles[i]);
    	// calc overall shape area of all circles
    	sumar += shape_area((shape *)&circles[i]);;
    }
    // print overall shape area
	printf("sum area%f\n",sumar );

    free(circles);	

    /*
    shape** shapearr = calloc(8, sizeof(*shapearr));
    shape *sarr = calloc(10, )
*/
    struct shapelink *root;
    struct shapelinke *actitem;

    root = malloc(sizeof(struct shapelink));
    fill_shapellist(root, 5);

    print_shapellist(root);
    print_shapellist(root);

    double *akku = malloc(sizeof(double));
    *akku = 9;
    printf("%d\n", akku);

//    root->next = 0;
//    root->s = malloc(sizeof(struct square));
    printf("%s %d \n", "sementation fault where are u?",shapellist_area(root,0));
     
    printf("%s %d \n", "sementation fault where are u?",3);
    free_shapellist(root);

    free(akku);


	//free(c);
	return 0;
}