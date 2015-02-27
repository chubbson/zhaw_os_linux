# automatically generated makefile by ../scripts/create-make

CFLAGS=-Wall -g -O2 -std=gnu99 -I. -I./include -L./lib

LIBS=-lcitsky -lm -lpthread


all: ULock sh_ex_lock H0_99_pow_rev

clean:
	rm -f  ULock sh_ex_lock H0_99_pow_rev lib/lib.o lib/isort.o lib/fsort.o lib/ternary-hsort.o lib/transmission-protocols.o lib/sort_common.o lib/psort.o lib/hsort.o lib/msort.o lib/fsort-metrics.o

ULock: ULock.c lib/libcitsky.a
	gcc $(CFLAGS) ULock.c $(LIBS) -o ULock

sh_ex_lock: sh_ex_lock.c lib/libcitsky.a
	gcc $(CFLAGS) sh_ex_lock.c $(LIBS) -o sh_ex_lock

H0_99_pow_rev: H0_99_pow_rev.c lib/libcitsky.a
	gcc $(CFLAGS) H0_99_pow_rev.c $(LIBS) -o H0_99_pow_rev

lib/lib.o: lib/lib.c
	gcc -c $(CFLAGS) lib/lib.c -o lib/lib.o

lib/isort.o: lib/isort.c
	gcc -c $(CFLAGS) lib/isort.c -o lib/isort.o

lib/fsort.o: lib/fsort.c
	gcc -c $(CFLAGS) lib/fsort.c -o lib/fsort.o

lib/ternary-hsort.o: lib/ternary-hsort.c
	gcc -c $(CFLAGS) lib/ternary-hsort.c -o lib/ternary-hsort.o

lib/transmission-protocols.o: lib/transmission-protocols.c
	gcc -c $(CFLAGS) lib/transmission-protocols.c -o lib/transmission-protocols.o

lib/sort_common.o: lib/sort_common.c
	gcc -c $(CFLAGS) lib/sort_common.c -o lib/sort_common.o

lib/psort.o: lib/psort.c
	gcc -c $(CFLAGS) lib/psort.c -o lib/psort.o

lib/hsort.o: lib/hsort.c
	gcc -c $(CFLAGS) lib/hsort.c -o lib/hsort.o

lib/msort.o: lib/msort.c
	gcc -c $(CFLAGS) lib/msort.c -o lib/msort.o

lib/fsort-metrics.o: lib/fsort-metrics.c
	gcc -c $(CFLAGS) lib/fsort-metrics.c -o lib/fsort-metrics.o



lib/libcitsky.a: lib/lib.o lib/isort.o lib/fsort.o lib/ternary-hsort.o lib/transmission-protocols.o lib/sort_common.o lib/psort.o lib/hsort.o lib/msort.o lib/fsort-metrics.o
	ar crs lib/libcitsky.a lib/lib.o lib/isort.o lib/fsort.o lib/ternary-hsort.o lib/transmission-protocols.o lib/sort_common.o lib/psort.o lib/hsort.o lib/msort.o lib/fsort-metrics.o
