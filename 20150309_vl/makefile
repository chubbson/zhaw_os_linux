# automatically generated makefile by ../scripts/create-make

CFLAGS=-Wall -g -O2 -std=gnu99 -I. -I./include -L./lib

LIBS=-lcitsky -lm -lpthread


all: tellwaitsmaple ipc daeomonize-group-signal H0_99_pow_rev HipcPCD_PCc_CDc_Cx_PDs_DPs forksample

clean:
	rm -f  tellwaitsmaple ipc daeomonize-group-signal H0_99_pow_rev HipcPCD_PCc_CDc_Cx_PDs_DPs forksample lib/error.o lib/lib.o lib/isort.o lib/fsort.o lib/ternary-hsort.o lib/transmission-protocols.o lib/sort_common.o lib/exec1.o lib/sig_tell_wait.o lib/psort.o lib/hsort.o lib/errorlog.o lib/msort.o lib/fsort-metrics.o

tellwaitsmaple: tellwaitsmaple.c lib/libcitsky.a
	gcc $(CFLAGS) tellwaitsmaple.c $(LIBS) -o tellwaitsmaple

ipc: ipc.c lib/libcitsky.a
	gcc $(CFLAGS) ipc.c $(LIBS) -o ipc

daeomonize-group-signal: daeomonize-group-signal.c lib/libcitsky.a
	gcc $(CFLAGS) daeomonize-group-signal.c $(LIBS) -o daeomonize-group-signal

H0_99_pow_rev: H0_99_pow_rev.c lib/libcitsky.a
	gcc $(CFLAGS) H0_99_pow_rev.c $(LIBS) -o H0_99_pow_rev

HipcPCD_PCc_CDc_Cx_PDs_DPs: HipcPCD_PCc_CDc_Cx_PDs_DPs.c lib/libcitsky.a
	gcc $(CFLAGS) HipcPCD_PCc_CDc_Cx_PDs_DPs.c $(LIBS) -o HipcPCD_PCc_CDc_Cx_PDs_DPs

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

lib/exec1.o: lib/exec1.c
	gcc -c $(CFLAGS) lib/exec1.c -o lib/exec1.o

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



lib/libcitsky.a: lib/error.o lib/lib.o lib/isort.o lib/fsort.o lib/ternary-hsort.o lib/transmission-protocols.o lib/sort_common.o lib/exec1.o lib/sig_tell_wait.o lib/psort.o lib/hsort.o lib/errorlog.o lib/msort.o lib/fsort-metrics.o
	ar crs lib/libcitsky.a lib/error.o lib/lib.o lib/isort.o lib/fsort.o lib/ternary-hsort.o lib/transmission-protocols.o lib/sort_common.o lib/exec1.o lib/sig_tell_wait.o lib/psort.o lib/hsort.o lib/errorlog.o lib/msort.o lib/fsort-metrics.o
