cl myprog.c
nmake // als make ersatz

H7 (2015-04-27)
Write a program for MS-Windows (Win32 or Win64) that
* opens a file
* reads the file
* does a sleep of a few seconds
* closes the file again.
Depending on the command line arguments, the file is opened exclusively or sharable. The actual file can be hard coded or preferably be given as command line argument.
Run the program multiple times simultanously to see the effect of exclusive and sharable usage of a file.

cl create-process.c
cl h1.c

create-process | starts 5 processes reading given file or fallback, if arg[1] is not 0 shared read is enabled otherwise disabled. after 3 seconds, it will terminate 1 subproc. 
arg[1] = 0 | 0 allows just 1 proc for read. 
           | everything else allows shared read
arg[2]     | defines file which should be read if not defined, ../temp/test-w-twice.txt will be read, hardcoded fallback

samples
create-process 			| starts 5 procs in read shared mode, reading ../temp/test-w-twice.txt
create-process 0 		| starts 5 procs but just one reading ../temp/test-w-twice.txt
create-process asdf		| starts 5 procs in read shared mode, reading ../temp/test-w-twice.txt
create-process asdf h1.c| starts 5 procs in read shared mode, reading h1.c
create-process 0 h1.c 	| starts 5 procs but just one reading h1.c

