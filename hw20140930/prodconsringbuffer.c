
/**
 * Author: David Hauri 
 * Thema: Ringbuffer with consumer / producer 
 * gcc Sample: gcc prodconsringbuffer.c -o prodconsringbuffer -lpthread
 * HINT: DONT Miss that -lpthread directive!!
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <limits.h>

#define BUFFERSIZE 300
#define NMAXPROD  3 // max nr of producer
#define NMAXCONS  3 // max nr of consumer
#define NMAX NMAXPROD+NMAXCONS
#define handle_error_en(en, msg) \
       do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
       do { perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct {
  int prodidx; 
  int considx;
  //int roundbalanceIndicator; 
  int buffer[BUFFERSIZE];
  int bufferSrcId[BUFFERSIZE];
  unsigned int counter;
  sem_t mutex; // enforce mutual excltion to shared data
  sem_t emptyslots; // keep track of the number of empty slots
  sem_t fullslots;  // keep track of the number of full slots
} ringbuffer;

struct thread_info {    /* Used as argument to thread_start() */
  pthread_t thread_id;        /* ID returned by pthread_create() */
  int       thread_num;       /* Application-defined thread # */
  ringbuffer *rb;             /* Pointer to Ringbuffer */
}; //ringbuffer shared;


// Description: 
//   get all values of ringbuffer from index 0 till fill 
// ringbuffer* rb: pointer to ringbuffer object
void print(const ringbuffer* rb) 
{
  int cnt = 0;
  int  i,j; 
  if(rb->prodidx > rb->considx)
  {
    cnt = rb->prodidx - rb->considx;
  }
  if(rb->prodidx < rb->considx)
  {
    cnt = BUFFERSIZE + rb->prodidx - rb->considx;
  }

  fflush(stdout);
  //printf("[P%d] Producing %d ...\n", index, item); 
  printf("passedFilling: %d | prodidx: %d | considx: %d | ElCnt: %d \n",rb->counter ,rb->prodidx,rb->considx, cnt);
  
  //printf("");
  // Iterate thru all fillded buffer index. 
  // from cons idx till prod index
  // add i to considx and mod buffersize till prod index
  for (i = 0; i < cnt; i++) 
  {
    j = (rb->considx)+i%BUFFERSIZE;
    printf("[%d|%d]:%d, ", rb->bufferSrcId[j], j, rb->buffer[j]);
  }

  fflush(stdout);
  puts(""); // do some newline :)  
  printf("\n Press any key to continue: \n");
  
  getchar();
}

// produce value to ring bufer. 
// if no empty slots avaliable, wait till they are.
// Description: add value x to ringbuffer
//   rb buffer of index rb idx++ = x value
//   rb idx is 1000 set it to 0; 
//   rb fill is less than 1000 increase 1
// x: addable value
// ringbuffer* rb: pointer to rb object
void speih(int srcid, int x, ringbuffer* rb) 
{
  //decrease empty slots if there any, if 0 -> wait
  sem_wait(&(rb->emptyslots));
  // if another thread uses buffer - wait
  sem_wait(&(rb->mutex));
  rb->bufferSrcId[rb->prodidx] = srcid;
  rb->buffer[rb->prodidx] = x;
  rb->prodidx = (rb->prodidx+1) % BUFFERSIZE;

  rb->counter++; 
  if(rb->counter%1000==0)
  { 
    print(rb);
  }

  // release buffer
  sem_post(&(rb->mutex));
  // increase the number of full slots
  sem_post(&(rb->fullslots));
  usleep(rand()%10000); // 1'000'000 = 1s => 10'000 = 0.01s
} 

// yum nomnomnomnom ... - consume an item
// if no full slots available .. wait with comuation.
int yum(ringbuffer* rb)
{
  // decrease full Slots if there any otherwise -> wait
  sem_wait(&(rb->fullslots));
  // if another thread uses buffer - wait
  sem_wait(&(rb->mutex));
  rb->bufferSrcId[rb->considx] = -1; 
  int res = rb->buffer[rb->considx]; 
  rb->considx = (rb->considx+1)%BUFFERSIZE;
  //checkBalancer(rb);
  // release buffer
  sem_post(&(rb->mutex));
  // incremet the number of empty slots
  sem_post(&(rb->emptyslots));
  usleep(rand()%10000); // 1'000'000 = 1s => 10'000 = 0.01s
  return res;
} 

// Start produce thread
// produces 1000 Items
void* prod_start(void *args)
{
  struct thread_info *tinfo = args;
  printf("Producer-thread '%d' started: rbidx=%d;\n",
           tinfo->thread_num, tinfo->rb->prodidx);

  int i,rval;
  for(i = 0; i < 1000; i++)
  {
    rval = rand()%100;
    printf("Thread %d [Produces]: i_idx %d; rand %d \n",tinfo->thread_num, i,rval);
    speih(tinfo->thread_num,rval,tinfo->rb);
  }
}

// Start consumer thread. 
// consumes 1000 Items
void* cons_start(void *args)
{

  struct thread_info *tinfo = args;
  printf("Consumer-thread '%d' started: rbidx=%d;\n",
           tinfo->thread_num, tinfo->rb->prodidx);

  int i,rval;
  for(i = 0; i < 1000; i++)
  {
    rval = yum(tinfo->rb);
    printf("Thread %d [consumes]: i_idx %d; val %d \n",tinfo->thread_num, i,rval);
  }
}

// Main function. start consumer produce thread and let they do their work
int main(int argc, char const *argv[])
{
  pthread_t idP; 
  int i, ptcres; 
  struct thread_info *tinfo;
  void  *res; 

  // seed random sequence
  srand(time(NULL));

  // initialize ringbuffer with index 0 and fill 0
  ringbuffer rb = { 0, 0, 0 };

  // Initialize semaphores
  sem_init(&rb.emptyslots, 0, BUFFERSIZE); // threadshared has buffersize empty slots
  sem_init(&rb.fullslots, 0 , 0); // threadshared - is locked
  sem_init(&rb.mutex, //pointer to semaphore
           0,               //0 if shared between threads, 1 if shared between processes 
           1);              // initaial value for semaphore (0 is locked)

  // allocate memorey for pthread_creat() arguments
  tinfo = calloc((NMAXPROD+NMAXCONS), sizeof(struct thread_info));
  if (tinfo == NULL)
    handle_error("calloc");
  
  // Create Producer
  for(i = 0; i < NMAXPROD; i++)
  {
    tinfo[i].thread_num = i; 
    tinfo[i].rb = &rb;

    // the pthread_create() call stores the thread id into corresponding element 
    // of tinfo[]
    ptcres = pthread_create(&tinfo[i].thread_id, NULL, &prod_start, &tinfo[i]);

    if (ptcres != 0)
      handle_error_en(ptcres, "pthread_create");
  }

  // Create Consumer
  for(i = NMAXPROD; i < NMAX; i++)
  {
    tinfo[i].thread_num = i; 
    tinfo[i].rb = &rb;

    // the pthread_create() call stores the thread id into corresponding element 
    // of tinfo[]
    ptcres = pthread_create(&tinfo[i].thread_id, NULL, &cons_start, &tinfo[i]);

    if (ptcres != 0)
      handle_error_en(ptcres, "pthread_create");
  }

  // join with each thread, and display its returned value */
  for (i = 0; i < NMAXPROD; i++) {
    ptcres = pthread_join(tinfo[i].thread_id, &res);
    if (ptcres != 0)
        handle_error_en(ptcres, "pthread_join");

    printf("Joined with thread %d; \n",
            tinfo[i].thread_num /*, (char *) res */);
    //free(res);      /* Free memory allocated by thread */
  }

  // Buffer, prod idx, cons idx should be restet 
  print(&rb); 

  // free semaphores
  sem_destroy(&((&rb)->mutex));
  sem_destroy(&((&rb)->fullslots));
  sem_destroy(&((&rb)->emptyslots));

  // free threadinfo
  free(tinfo);
  exit(EXIT_SUCCESS);

  return (1);
}
