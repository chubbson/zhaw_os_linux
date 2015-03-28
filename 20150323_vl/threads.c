/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri
 * Date: 2015-03-20
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

/*
Blocking nonblocking verwenden
mutex initialisieren
mehrere threads starten 
jeder thread vresucht mutex zu bekommen, liest eine zeile der eingabe und gibt die aus
nachach leep(1) dann mutex freigeben
*/

#include <apue.h>
#include <itskylib.h>
#include <pthread.h>
#include <errno.h>

#define handle_error_en(en, msg) \
       do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

struct thread_info {    /* Used as argument to thread_start() */
  pthread_t thread_id;        /* ID returned by pthread_create() */
  int       thread_num;       /* Application-defined thread # */
  //ringbuffer *rb;             /* Pointer to ringbuffer var */
}; //ringbuffer shared;


pthread_mutex_t lock;
int ctr = 0; 

void *threadwork(void *args)
{
	pthread_mutex_lock(&lock);
	ctr++; 

	printf("ctr: %d started\n", ctr);
	sleep(1);
	printf("ctr: %d finished\n", ctr);

	pthread_mutex_unlock(&lock);
  return NULL;
}

int main(int argc, char const *argv[])
{
	int ptcres;
	struct thread_info *tinfo;
	int i, nmax = 5; 
  void  *res; 

	// allocate memorey for pthread_creat() arguments
  tinfo = calloc(nmax, sizeof(struct thread_info));
  if (tinfo == NULL)
    err_sys("calloc");


  if (pthread_mutex_init(&lock, NULL) != 0)
  {
      printf("\n mutex init failed\n");
      return 1;
  }
  
	// Create Producer
  for(i = 0; i < nmax; i++)
  {
    tinfo[i].thread_num = i; 
//    tinfo[i].rb = &rb;

    // the pthread_create() call stores the thread id into corresponding element 
    // of tinfo[]
    ptcres = pthread_create(&tinfo[i].thread_id, NULL, &threadwork, &tinfo[i]);
    if (ptcres != 0)
      handle_error_en(ptcres, "pthread_create");

    printf("thread created: %d; \n",
        tinfo[i].thread_num);
  }

  // join with each thread, and display its returned value */
  for (i = 0; i < nmax; i++) {
    ptcres = pthread_join(tinfo[i].thread_id, &res);
    if (ptcres != 0)
        handle_error_en(ptcres, "pthread_join");

    printf("Joined with thread %d; \n",
            tinfo[i].thread_num /*, (char *) res */);
    //free(res);      /* Free memory allocated by thread */
  }

  pthread_mutex_destroy(&lock);

  // free threadinfo
  free(tinfo);
  exit(EXIT_SUCCESS);
}