#include "apue.h"
#include <sys/wait.h> 
#include <itskylib.h>
#include <kb.h>

static struct termios orig_termios_struct;

int main(int argc, char const *argv[])
{
	char line[MAXLINE];
	FILE *fpin;

	struct termios termios_struct;
  tcgetattr(STDIN_FILENO, &orig_termios_struct);
  tcgetattr(STDIN_FILENO, &termios_struct);
  // could be done like this also:
  // termios_struct = orig_termios_struct;

  termios_struct.c_lflag &= (~ICANON) & (~ECHO);
  termios_struct.c_cc[VTIME] = 0;
  termios_struct.c_cc[VMIN] = 1;
  tcsetattr(STDIN_FILENO, TCSANOW, &termios_struct);
  sleep(1);

  printf("test");

	//sprintf(line, MAXLINE, "./kbfilter < %s", STDIN_FILENO                                                                                                               )
	if((fpin = popen("./kbfilter2", "r")) == NULL)
		err_sys("popen error"); 

  printf("test2");                           
	for(;;)
	{
		//fputs("prompt> ", stdout);
		//fflush(stdout);
		if(fgets(line, MAXLINE, fpin) == NULL) // read from pipe
		{
			printf("test3");    
			err_sys("fputs error to pipe");
			break;
		}
		if(fputs(line, stdout) == EOF)
		{
			printf("test4");    
  		tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
			err_sys("fputs error to pipe");
		}
		fflush(stdout);
	}

  printf("after for test");

  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
	if(pclose(fpin) == -1)
		err_sys("pclose error");

	putchar('\n');
	exit(0);
}