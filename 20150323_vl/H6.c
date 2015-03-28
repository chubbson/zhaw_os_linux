/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri
 * Date: 2015-03-20
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

/*
 * threads und mutex oder RW-lock
 * programm bekommt beliebig vilee dateinamen als argumente übergeben. 
 * für jedes argument werden ein thread gestartet
 * thread liest diese datei (oder named pipe)
 * jede datei entrhält short-werte, jeweils 2byte. 
   wenn ungerade anzahl dann 0byte angehängt dazudenken. 
 * zählen  wie häufig die short werte vorkommen
 * zählung im memory
 * mehrere threads dieser art laufen gleichzeitig
 * wenn ein thread fertig ist, zwischenergebnis ausgeben
 * rwlocks ode mutex benutzen um gegenseitige störtung zu verhindern
 */

/* pthread_barrier_sample
 * barriere.c
 **/

#include <apue.h>
#include <itskylib.h>
#include <pthread.h>
#include <errno.h>
#include <limits.h>
#include <sys/file.h>

#define handle_error_en(en, msg) \
  do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct {
  int resarr[USHRT_MAX];
  pthread_mutex_t mutarr[USHRT_MAX];
} counterstruct;

struct thread_info {    /* Used as argument to thread_start() */
  pthread_t thread_id;        /* ID returned by pthread_create() */
  int       thread_num;       /* Application-defined thread # */
  char *    argfile;
  counterstruct  *cs;         /* Pointer to counterstruct var */   
}; //counterstruct shared;

pthread_mutex_t lock;
int ctr = 0; 

void initmutarr(counterstruct* cs)
{
	int i = 0; 
	for(i = 0; i < USHRT_MAX; i++)
	{
		if (pthread_mutex_init(&cs->mutarr[i],NULL) != 0) //lock, NULL)!=0)// (cs->mutarr[i]), NULL) != 0)
	    printf("\n mutex #'%d' in mutarr - init failed\n", i);
	}
}

void cleanmutarr(counterstruct* cs)
{
	int i = 0; 
	for(i = 0; i < USHRT_MAX; i++)
	{
		if (pthread_mutex_destroy(&cs->mutarr[i]) != 0)
	    printf("\n mutex #'%d' in mutarr - clean failed\n", i);
	}
}

void incshortarr(counterstruct* cs, short shrt)
{
	short i = shrt;
	pthread_mutex_lock(&cs->mutarr[i]);
	cs->resarr[i]++;
	pthread_mutex_unlock(&cs->mutarr[i]);
}

// Description: 
//   get all values of ringbuffer from index 0 till fill 
// ringbuffer* rb: pointer to ringbuffer object
void print(const counterstruct* cs) 
{
	printf("buftst sizeof size %d\n", USHRT_MAX);
	int i = 0; 
	for(i = 0; i < USHRT_MAX; i++)
	{	
		if(cs->resarr[i] > 0)
			printf("#%d \tcnt: %d\n", i, cs->resarr[i]);
	}
}

void * threadwork(void *args)
{
	struct thread_info *tinfo = args;
  printf("thread num '%d' started\n", //: rbidx=%d;\n",
         tinfo->thread_num/*, tinfo->rb->prodidx*/);

  printf("args name: '%s' \n", tinfo->argfile);
  // check if args is file
  // check if args is pipe 


  int fd = open(tinfo->argfile, O_RDONLY, 0666);
  handle_error(fd, "fopen", PROCESS_EXIT);

  // trying shared lock 
  //printf("trying to lock (sh) file pid=%d\n", pid);
  int retcode = flock(fd, LOCK_SH);
  handle_error(retcode, "flock LOCK_SH", PROCESS_EXIT);

	off_t pos = lseek(fd, 0, SEEK_SET);
	handle_error(pos, "lseek for read", PROCESS_EXIT);

	unsigned short resbuf[1];
	ssize_t s;
	//int j = 0;
 
  // read file / pipe
	while ((s = read(fd, resbuf, sizeof(short))) > 0) {
	  //printf("%d\n", j++);

    // inc short cntr
	  incshortarr(tinfo->cs, resbuf[0]);
	}
	handle_error(s, "lseek for read", PROCESS_EXIT);

	retcode = flock(fd, LOCK_UN);
  handle_error(retcode, "flock LOCK_UN", PROCESS_EXIT);

  // leave thread
	printf("thread num '%d' finished\n", //: rbidx=%d;\n",
         tinfo->thread_num/*, tinfo->rb->prodidx*/);
  return NULL;
}


int main(int argc, char *argv[])
{
	int ptcres;
	struct thread_info *tinfo;
	int i, nmax = (argc-1); 
  void  *res;   
  // initialize ringbuffer with index 0 and fill 0
  counterstruct cs;// no init needed .. = { 0, 0 };

  initmutarr(&cs);

	// allocate memorey for pthread_creat() arguments
  tinfo = calloc(nmax, sizeof(struct thread_info));
  if (tinfo == NULL)
    err_sys("calloc");


  if (pthread_mutex_init(&lock, NULL) != 0)
  {
      printf("\n mutex init failed\n");
      return 1;
  }
  
// pthread_barrier_init, 

	// Create Producer
  for(i = 0; i < nmax; i++)
  {
    tinfo[i].thread_num = i; 
    tinfo[i].argfile = argv[i+1];
    tinfo[i].cs = &cs;

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


  cleanmutarr(&cs);


  print(&cs); 

  // free threadinfo
  free(tinfo);
  exit(EXIT_SUCCESS);
}