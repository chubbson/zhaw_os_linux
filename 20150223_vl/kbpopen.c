#include "apue.h"
#include <sys/wait.h> 
#include <itskylib.h>
#include <kb.h>

static struct termios orig_termios_struct;

int main(int argc, char const *argv[])
{
	char line[MAXLINE];
	FILE *fpout, *fpin;

	if((fpout = popen("./kbfilter", "w")) == NULL)
			err_sys("popen error");
	//if((fpin = popen("./kbfilter", "r")) == NULL)
	//		err_sys("popen error");

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

  char c[2];
  //while((c = getchar()) != EOF)
  while((c[0] = getc(stdin)) != EOF)
	{   
		c[1] = 0;    
		//printf("%s\n", c);
		if(fputs(c,fpout) == EOF)
		{ 
  		tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
			err_sys("fputs error to pipe");
		}
	}
  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
	if (ferror(fpout))
		//||ferror(fpin))
		err_sys("fputs error to pipe");
  if(pclose(fpout) == -1)
		err_sys("pclose fpout error");
  //if(pclose(fpin) == -1)
	//	err_sys("pclose fpin error");
/*
	if((fpin = popen("./kbfilter", "r")) == NULL)
			err_sys("popen error");
	for(;;)
	{
		//fputs("prompt> ", stdout);
		//fflush(stdout);
		if(fgets(line, MAXLINE, fpin) == NULL) // read from pipe
			break;
		if(fputs(line, stdout) == EOF)
			err_sys("fputs error to pipe");
	}
	if(pclose(fpin) == -1)
		err_sys("pclose error");

//	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
*/
	putchar('\n');
	exit(0);
}