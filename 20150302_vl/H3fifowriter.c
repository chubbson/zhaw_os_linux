/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri
 * Date: 2015-03-21
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

/*
 * H3 (2015-03-21):
 * fiforeader
**/
#include <apue.h>
#include <itskylib.h>

int main(int argc, char *argv[])
{

	char * TEMPFIFO = "temp.fifo2";
	//char * TEMPFIFO = "test.txt";
	int res, n; 
  char buf[MAXLINE];
	int fdwrite;
	printf("%s\n", "before unlink");
  unlink(TEMPFIFO);
	printf("%s\n", "after unlink");

  // create the FIFO (named pipe) 
  //0777
  res = mkfifo(TEMPFIFO, 0777);
	handle_error(res, "mkfifo", PROCESS_EXIT);

	printf("%s\n", "after mkfifo");
	printf("waits till any reader connected to fifo %s\n", TEMPFIFO);

	// waits till anyone is reading
	if((fdwrite = open(TEMPFIFO, O_WRONLY)) < 0)
		handle_error(fdwrite, "open write", PROCESS_EXIT);

	printf("%s\n", "after open");

	int i = 0;
	while (i++ < 30)
	{			
		n = sprintf(buf, "%d of %d\n", i, 30);
		printf("printf n: %d, m: %s", n, buf);
		if(write(fdwrite, buf, n) != n)
			err_sys("write error to named pipe");
		sleep(1);
	}

	res = close(fdwrite);
		handle_error(res, "fclose fp_fifo", PROCESS_EXIT);

	printf("%s\n", "fifowriter exit");
	exit(0);
}