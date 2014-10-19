# automatically generated makefile by ../scripts/create-make

CFLAGS=-Wall -g -O2 -std=gnu99 -I. -I./include -L./lib

LIBS=-lcitsky -lm -lpthread


all: linkedlist polimorphical-simpson polimorphical-hw realloc

clean:
	rm -f  linkedlist polimorphical-simpson polimorphical-hw realloc

linkedlist: linkedlist.c lib/libcitsky.a
	gcc $(CFLAGS) linkedlist.c $(LIBS) -o linkedlist

polimorphical-simpson: polimorphical-simpson.c lib/libcitsky.a
	gcc $(CFLAGS) polimorphical-simpson.c $(LIBS) -o polimorphical-simpson

polimorphical-hw: polimorphical-hw.c lib/libcitsky.a
	gcc $(CFLAGS) polimorphical-hw.c $(LIBS) -o polimorphical-hw

realloc: realloc.c lib/libcitsky.a
	gcc $(CFLAGS) realloc.c $(LIBS) -o realloc



lib/libcitsky.a:
	ar crs lib/libcitsky.a
