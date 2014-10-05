
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

const int BUFFERSIZE = 1000; 

typedef struct ringbuffer {
  int prodidx; 
  int considx;
  int roundbalanceIndicator; 
  int buffer[1000];
  sem_t mutex;
} ringbuffer;

// Description: add value x to ringbuffer
//   rb buffer of index rb idx++ = x value
//   rb idx is 1000 set it to 0; 
//   rb fill is less than 1000 increase 1
// x: addable value
// ringbuffer* rb: pointer to rb object
void speih(int x, ringbuffer* rb) 
{
  sem_wait (&(rb->mutex));
  rb->buffer[rb->prodidx++] = x;
  if (rb->prodidx == BUFFERSIZE) 
  {   
    rb->roundbalanceIndicator = 1;
    rb->prodidx = 0;
  }
  checkBalancer(&rb);
  sem_post (&(rb->mutex));
} 

int yum(ringbuffer* rb)
{
  sem_wait (&(rb->mutex));
  int res = rb->buffer[rb->considx++]; 
  if (rb->considx == BUFFERSIZE) 
  {   
    rb->roundbalanceIndicator = 0;
    rb->considx = 0;
  }
  checkBalancer(&rb);
  sem_post (&(rb->mutex));

  return res;
}

void checkBalancer(ringbuffer* rb)
{   
  if(rb->prodidx == rb->considx)
  { 
    if(rb->roundbalanceIndicator)
    {
      // stop produces
    }
    else
    {
      // stop consumer
    }    
  }
}
 

// Description: 
//   get all values of ringbuffer from index 0 till fill 
// ringbuffer* rb: pointer to ringbuffer object
void print(const ringbuffer* rb) 
{
  printf("prodidx:%d|considx:%d \n",rb->prodidx,rb->considx);
  int i;

  // Iterate thru all fillded buffer index. 
  // from cons idx till prod index
  // add i to considx and mod buffersize till prod index
  for (i = 0; ((rb->considx)+i)%BUFFERSIZE < (rb->prodidx)  ; i++) 
  {
    printf("[%d]:%d, ",i, rb->buffer[i]);
  }
  puts(""); // do some newline :)  
}

int main(int argc, char const *argv[])
{
  int i; 

  // initialize ringbuffer with index 0 and fill 0
  ringbuffer rb = { 0, 0, 0 };
  sem_init(&((&rb)->mutex), 0, 1);

  int r = rand() % 20;

  printf("rand: %d\n", r);

  return (1);
  /*
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
  */
}
