# automatically generated makefile by ../scripts/create-make

CFLAGS=-Wall -g -O2 -std=gnu99 -I. -I./include -L./lib

LIBS=-lcitsky


all: hw_vfork sleep_ex hw_execfork hw_exec hw_fork sleep

clean:
	rm -f  hw_vfork sleep_ex hw_execfork hw_exec hw_fork sleep

hw_vfork: hw_vfork.c lib/libcitsky.a
	gcc $(CFLAGS) hw_vfork.c $(LIBS) -o hw_vfork

sleep_ex: sleep_ex.c lib/libcitsky.a
	gcc $(CFLAGS) sleep_ex.c $(LIBS) -o sleep_ex

hw_execfork: hw_execfork.c lib/libcitsky.a
	gcc $(CFLAGS) hw_execfork.c $(LIBS) -o hw_execfork

hw_exec: hw_exec.c lib/libcitsky.a
	gcc $(CFLAGS) hw_exec.c $(LIBS) -o hw_exec

hw_fork: hw_fork.c lib/libcitsky.a
	gcc $(CFLAGS) hw_fork.c $(LIBS) -o hw_fork

sleep: sleep.c lib/libcitsky.a
	gcc $(CFLAGS) sleep.c $(LIBS) -o sleep



lib/libcitsky.a:
	ar crs lib/libcitsky.a
