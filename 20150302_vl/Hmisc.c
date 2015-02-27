
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <itskylib.h>

#define READ_BUF_SIZE 20

int main(int argc, char const *argv[])
{

	const char *FILENAME = "out-lowlevel.txt";
  int f = open(FILENAME, O_RDONLY, 0666);
  handle_error(f, "fopen", PROCESS_EXIT);
  int pid = getpid();

  // try non-blocking-lock 
  int retcode;

  // trying shared lock 
  printf("trying to lock (sh) file pid=%d\n", pid);
  retcode = flock(f, LOCK_SH);
  handle_error(retcode, "flock LOCK_SH", PROCESS_EXIT);

	off_t pos = lseek(f, 0, SEEK_SET);
	handle_error(pos, "lseek for read", PROCESS_EXIT);

	while (TRUE) {
	  char buf[READ_BUF_SIZE];
	  ssize_t s = read(f, buf, READ_BUF_SIZE);
	  handle_error(s, "read", PROCESS_EXIT);
	  if (s == 0) {
	    break;
	  }
	  //write(STDOUT_FILENO, buf, s);
	  fwrite(buf, s, 1, stdout);
	  sleep(1);
	}
}