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
	int res; 
  char buf[MAXLINE];
	int fdread;

	if((fdread = open(TEMPFIFO, O_RDONLY | O_NONBLOCK)) < 0)
		handle_error(fdread, "open read", PROCESS_EXIT);

/*
	FILE *fp_fifo;
	
	if((fp_fifo = fdopen(fdread, "r")) == NULL)	
		err_sys("fdopen error");

	while (fgets(buf, sizeof buf, fp_fifo) != NULL)
	{
		printf("%s: %s", "msg read", buf);
	}
*/
	int numRead; 
	for (;;) {              /* Read data from pipe, echo on stdout */
		numRead = read(fdread, buf, MAXLINE);
		//handle_error(numRead, "read", PROCESS_EXIT)
		if (numRead == -1)
		  //errExit("read");
		if (numRead == 0)
		  break;                      /* End-of-file */
		if (write(STDOUT_FILENO, buf, numRead) != numRead)
      err_sys("child - partial/failed write");
  }

//	res = fclose(fp_fifo);
//		handle_error(res, "fclose fp_fifo", PROCESS_EXIT);

  // fdread must not be closed cuz fp_already closed
	res = close(fdread);
		handle_error(res, "close fdread", PROCESS_EXIT);
}