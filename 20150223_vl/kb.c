/* (C) Hauronen Patronens waste of time projects!
* https://github.com/chubbson/zhaw_os_linux
* Author: David Hauri
* Date: 2014-03-01
* License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
*/

#include <apue.h>
#include <itskylib.h>
#include <kb.h>

int main(int argc, char const *argv[])
{
	/*
	FILE *fpout; 


  struct termios termios_struct;
  struct termios orig_termios_struct;

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
  
  /*if((fpout = popen(STDOUT_FILENO, "w")) == NULL)
  	err_sys("popen error");
	*/


  struct termios termios_struct;
  struct termios orig_termios_struct;

  tcgetattr(STDIN_FILENO, &orig_termios_struct);
  tcgetattr(STDIN_FILENO, &termios_struct);
  // could be done like this also:
  // termios_struct = orig_termios_struct;

  termios_struct.c_lflag &= (~ICANON) & (~ECHO);
  termios_struct.c_cc[VTIME] = 0;
  termios_struct.c_cc[VMIN] = 1;
  tcsetattr(STDIN_FILENO, TCSANOW, &termios_struct);
  sleep(1);


  while (1) {
  	
    char inkey[1];

    int b = read(STDIN_FILENO, inkey, 1);
    if (b < 1) {
      printf("nothing read\n");
      continue;
    }

/*
	  enum kb_binds key;
	  if (inkey == 'd' || inkey == 'l') {
	    key = NEXT;
	  } else if (inkey == 'a' || inkey == 'h') {
	    key = PREV;
	  } else if (inkey == 's' || inkey == 'j' || inkey == '\n') {
	    key = NEXTLINE;
	  } else if (inkey == 'w' || inkey == 'k') {
	    key = PREVLINE;
	  } else if (inkey == 'q') {
	    key = QUIT;
	  } else if (inkey == 'i' || inkey == '?') {
	    key = HELP;
	  } else {
	  	key = NONE;
	  }
*/
	  int res = write(STDOUT_FILENO, inkey, 1);//&key, sizeof(enum kb_binds));

	  if(res != 1)
	 	{
	  	err_sys("write error, key enum to stdout'%d','%d'",res, sizeof(enum kb_binds));
	  	break;
	  }
	  else
	  {
	  	printf("'%s'\n", inkey);
	  	//printf("'%d'\n", stringlen(inkey));
	  }
/*
	  if(key == QUIT)
	  {
	  	break;
	  }
	  */

    if(inkey == 'q')
    	break;

	}


  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);

	/* code */
	return 0;
}