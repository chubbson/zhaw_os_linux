#Makefile
../scripts/create-make > makefile
- make 
- make all
- make clean

#Execution
*run normal*

- ./ringbuffer

*run with errorcode*

- ./prodconsringbuffer
