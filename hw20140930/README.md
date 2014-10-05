#Makefile
../scripts/create-make > makefile
-make 
-make all
-make clean

# run normal
./ringbuffer
# run with errorcode
./prodconsringbuffer
