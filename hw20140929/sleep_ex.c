#include <stdio.h>
#include <unistd.h>

#include <stdlib.h> // Declaration for exit();

main(int argc, char * argv[])
{
  int i, extcd = 0;
  //printf("Argument count=%d\n",argc);
  for (i = 1; i < argc; i++) {
    extcd += strlen(argv[i]);
    printf("Argument %s %d\n",argv[i],extcd);
  }

  int res;
  unsigned int ui;

  printf("my prorc ID: %d \n", getpid());

  for(i=0;i<5;i++)
  {
    res =0;
    ui = 1000000;
    usleep(ui);    
//    sleep(1);
//    useconds_t duration = (useconds_t) (ABS(rand()%1000000));
//    usleep(1000);
    printf("cnt: %d rescode: %d\n", (i*i), res);

// ps uow legrep 'PID|3662'
// ps -ef
///bsd
// ps -x
  }
  printf("Return value: %d \n", extcd);
  exit(extcd);
}
