
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

const int BUFFERSIZE = 10; 

typedef struct {
  int idx; 
  int fill;
  int minIdx;
  int buffer[10];
} ringbuffer;

// Description: add value x to ringbuffer
//   rb buffer of index rb idx++ = x value
//   rb idx is 1000 set it to 0; 
//   rb fill is less than 1000 increase 1
// x: addable value
// ringbuffer* rb: pointer to rb object
void add(int x, ringbuffer* rb) 
{
  rb->buffer[rb->idx++] = x;
  if (rb->idx == BUFFERSIZE)  
    rb->idx = 0;

  if (rb->fill < BUFFERSIZE) 
    (rb->fill)++;
} 

// Description: 
//   get all values of ringbuffer from index 0 till fill 
// ringbuffer* rb: pointer to ringbuffer object
void print(const ringbuffer* rb) 
{
  printf("idx:%d|fill:%d \n",rb->idx,rb->fill);
  int i;
  for (i = 0; i < rb->fill; i++) 
  {
    printf("[%d]:%d, ",i, rb->buffer[i]);
  }
  puts(""); // do some newline :)
}

int main(int argc, char const *argv[])
{
  int i; 

  // initialize ringbuffer with index 0 and fill 0
  ringbuffer rb = { 0, 0 };

  puts("empty:");
  // get pointer of rb object and put it into print
  print(&rb);

  // add 1 till 5 into ringbuffer
  for (i = 1; i <= 5; i++)
  {
    add(i, &rb);
  }

  puts("+5");
  print(&rb);

  // add 5 till 10 into ringbuffer
  for (i = 6; i <= 10; i++)
  {
    add(i, &rb);  
  } 

  puts("+5");
  print(&rb);

  // add 10 till 15 5o ringbuffer
  for (i = 11; i <= 15; i++)
  { 
    add(i, &rb);
  }
  puts("+5");
  print(&rb);

  return 0;
}
