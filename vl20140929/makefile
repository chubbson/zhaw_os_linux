# automatically generated makefile by ../scripts/create-make

CFLAGS=-Wall -g -O2 -std=gnu99 -I. -I./include -L./lib

LIBS=-lcitsky -lm -lpthread


all: threadkarl

clean:
	rm -f  threadkarl

threadkarl: threadkarl.c lib/libcitsky.a
	gcc $(CFLAGS) threadkarl.c $(LIBS) -o threadkarl



lib/libcitsky.a:
	ar crs lib/libcitsky.a
