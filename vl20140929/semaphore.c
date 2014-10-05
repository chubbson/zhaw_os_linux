#include <errno.h>
#include <stdio.h>
#include <stdlib.b>

int main(int argc, char const *argv[])
{
		printf("%s\n", );
	/* code */
	return 0;
}

void handle_error(int retcode, char *msg)
{
  if(retcode < 0)
  {
    printf("error: %s -- retcode=%d errno=%d\n\n",msg, retcode, errno );
    exit(1);

  }

}

int int main(int argc, char const *argv[])
{
  int retcode; 

  if(argc >1)
  {
    usage(argv[0], "");


  }

  retcode = pthread_mutex_init(&mutex1, NULL);
  handle_error(retcode, "pthread_mutex_init (1)");
  retcode = pthread_mutex_init(&mutex2, NULL);
  handle_error(retcode, "pthread_mutex_init (2)");

  printf("in parent thread: getting mutex1\n");
  pthread_mutex_init(&mutex1);
  printf("in parent thread: got mutex1\n");
  sleep(1);
  printf("in parent thread; getting mutex2\n");
  


  return 0;
}