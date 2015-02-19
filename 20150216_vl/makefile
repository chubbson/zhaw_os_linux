# automatically generated makefile by ../scripts/create-make

CFLAGS=-Wall -g -O2 -std=gnu99 -I. -I./include -L./lib

LIBS=-lcitsky -lm -lpthread


all: U0_99_pow H0_99_pow_rev

clean:
	rm -f  U0_99_pow H0_99_pow_rev

U0_99_pow: U0_99_pow.c lib/libcitsky.a
	gcc $(CFLAGS) U0_99_pow.c $(LIBS) -o U0_99_pow

H0_99_pow_rev: H0_99_pow_rev.c lib/libcitsky.a
	gcc $(CFLAGS) H0_99_pow_rev.c $(LIBS) -o H0_99_pow_rev



lib/libcitsky.a:
	ar crs lib/libcitsky.a
