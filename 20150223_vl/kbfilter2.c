#include "apue.h"
#include <ctype.h>

static struct termios orig_termios_struct;

int main(void)
{
/*
  if (setvbuf(stdin,NULL,_IONBF,0) != 0)
  	err_sys("setvbuf error");
  if (setvbuf(stdout,NULL,_IONBF,0) != 0)
  	err_sys("setvbuf error");
*/
  /*
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
*/
	int c; 
	while((c = getchar()) != EOF)
	{
		
		if(isupper(c))
			c = tolower(c);
		if(putchar(c) == EOF)
			err_sys("output error");

		char buf[2];
		buf[0] = (char)c;
		buf[1] = 0;
		write(STDOUT_FILENO, buf, 2);
		fflush(stdout);
	}
	exit(0);
//	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
}