# automatically generated makefile by ../scripts/create-make

CFLAGS=-Wall -g -O2 -std=gnu99 -I. -I./include -L./lib

LIBS=-lcitsky -lm -lpthread


all: fopenprintfsample coprocessSample Hmisc H3 kbfilter H3fiforeader H3fifowriter H0_99_pow_rev forksample

clean:
	rm -f  fopenprintfsample coprocessSample Hmisc H3 kbfilter H3fiforeader H3fifowriter H0_99_pow_rev forksample lib/error.o lib/lib.o lib/isort.o lib/fsort.o lib/ternary-hsort.o lib/transmission-protocols.o lib/sort_common.o lib/read_line.o lib/exec1.o lib/clrfl.o lib/setfl.o lib/sig_tell_wait.o lib/psort.o lib/hsort.o lib/errorlog.o lib/msort.o lib/fsort-metrics.o

fopenprintfsample: fopenprintfsample.c lib/libcitsky.a
	gcc $(CFLAGS) fopenprintfsample.c $(LIBS) -o fopenprintfsample

coprocessSample: coprocessSample.c lib/libcitsky.a
	gcc $(CFLAGS) coprocessSample.c $(LIBS) -o coprocessSample

Hmisc: Hmisc.c lib/libcitsky.a
	gcc $(CFLAGS) Hmisc.c $(LIBS) -o Hmisc

H3: H3.c lib/libcitsky.a
	gcc $(CFLAGS) H3.c $(LIBS) -o H3

kbfilter: kbfilter.c lib/libcitsky.a
	gcc $(CFLAGS) kbfilter.c $(LIBS) -o kbfilter

H3fiforeader: H3fiforeader.c lib/libcitsky.a
	gcc $(CFLAGS) H3fiforeader.c $(LIBS) -o H3fiforeader

H3fifowriter: H3fifowriter.c lib/libcitsky.a
	gcc $(CFLAGS) H3fifowriter.c $(LIBS) -o H3fifowriter

H0_99_pow_rev: H0_99_pow_rev.c lib/libcitsky.a
	gcc $(CFLAGS) H0_99_pow_rev.c $(LIBS) -o H0_99_pow_rev

forksample: forksample.c lib/libcitsky.a
	gcc $(CFLAGS) forksample.c $(LIBS) -o forksample

lib/error.o: lib/error.c
	gcc -c $(CFLAGS) lib/error.c -o lib/error.o

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

lib/read_line.o: lib/read_line.c
	gcc -c $(CFLAGS) lib/read_line.c -o lib/read_line.o

lib/exec1.o: lib/exec1.c
	gcc -c $(CFLAGS) lib/exec1.c -o lib/exec1.o

lib/clrfl.o: lib/clrfl.c
	gcc -c $(CFLAGS) lib/clrfl.c -o lib/clrfl.o

lib/setfl.o: lib/setfl.c
	gcc -c $(CFLAGS) lib/setfl.c -o lib/setfl.o

lib/sig_tell_wait.o: lib/sig_tell_wait.c
	gcc -c $(CFLAGS) lib/sig_tell_wait.c -o lib/sig_tell_wait.o

lib/psort.o: lib/psort.c
	gcc -c $(CFLAGS) lib/psort.c -o lib/psort.o

lib/hsort.o: lib/hsort.c
	gcc -c $(CFLAGS) lib/hsort.c -o lib/hsort.o

lib/errorlog.o: lib/errorlog.c
	gcc -c $(CFLAGS) lib/errorlog.c -o lib/errorlog.o

lib/msort.o: lib/msort.c
	gcc -c $(CFLAGS) lib/msort.c -o lib/msort.o

lib/fsort-metrics.o: lib/fsort-metrics.c
	gcc -c $(CFLAGS) lib/fsort-metrics.c -o lib/fsort-metrics.o



lib/libcitsky.a: lib/error.o lib/lib.o lib/isort.o lib/fsort.o lib/ternary-hsort.o lib/transmission-protocols.o lib/sort_common.o lib/read_line.o lib/exec1.o lib/clrfl.o lib/setfl.o lib/sig_tell_wait.o lib/psort.o lib/hsort.o lib/errorlog.o lib/msort.o lib/fsort-metrics.o
	ar crs lib/libcitsky.a lib/error.o lib/lib.o lib/isort.o lib/fsort.o lib/ternary-hsort.o lib/transmission-protocols.o lib/sort_common.o lib/read_line.o lib/exec1.o lib/clrfl.o lib/setfl.o lib/sig_tell_wait.o lib/psort.o lib/hsort.o lib/errorlog.o lib/msort.o lib/fsort-metrics.o
