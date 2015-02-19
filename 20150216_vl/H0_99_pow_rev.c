#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{	
  // 5 Bytes pro eintrag. 
  // nur line feed. 
  const char *FILENAME = "out-lowlevel.txt";
  // man 2 write

  int i,m,n;
  int fdout;
  char res[6];

  n = 5;
  fdout = open(FILENAME, O_WRONLY | O_CREAT);
  printf("fdout=%d\n", fdout);
  for(i = 99; i >= 0; i--)
  { 
    lseek(fdout, i*n, SEEK_SET);
    sprintf(res,"%4d\n",i*i);
    m = write(fdout, res, n);
    printf("%d bytes written (lenght %d)\n", m, n);
  }
  close(fdout);

  return 0;
}
