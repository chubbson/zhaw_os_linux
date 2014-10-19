# automatically generated makefile by ../scripts/create-make

CFLAGS=-Wall -g -O2 -std=gnu99 -I. -I./include -L./lib

LIBS=-lcitsky -lm -lpthread


all: prodconsringbuffer ringbuffer

clean:
	rm -f  prodconsringbuffer ringbuffer

prodconsringbuffer: prodconsringbuffer.c lib/libcitsky.a
	gcc $(CFLAGS) prodconsringbuffer.c $(LIBS) -o prodconsringbuffer

ringbuffer: ringbuffer.c lib/libcitsky.a
	gcc $(CFLAGS) ringbuffer.c $(LIBS) -o ringbuffer



lib/libcitsky.a:
	ar crs lib/libcitsky.a
