/* (C) Hauronen Patronens waste of time projects!
* https://github.com/chubbson/zhaw_os_linux
* Author: David Hauri
* Date: 2014-02-27
* License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
*/

// less oder more schreiben. 
// zeile vor, zeile zurück gehen. 
// next char
// prev char

// direkt auf tastendruck reagieren, nicht zuerst taste dann return!
// setbuff, setvbuff

// int x;
// scanf("%d",&x)

//strcmp gute approx für utf-8
// wandet byteseq der versch. encodings - iconv

// od -x old.utf8.txt | head -20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <termios.h>
#include <itskylib.h>

enum kb_binds { NONE, NEXT, PREV, NEXTLINE, PREVLINE, QUIT, HELP };
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
  printf("locked (ex) file pid=%d\n", pid);

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

	off_t pos = lseek(f, 0, SEEK_SET);
	handle_error(pos, "lseek for read", PROCESS_EXIT);

  while (1) {
  	
    char inkey;
    int b = read(STDIN_FILENO, &inkey, 1);
    if (b < 1) {
      printf("1nothing read\n");
      continue;
    }

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

	  switch(key){
	  	case HELP:
	  	  printf("\n=====HELP=====\n");
	  	  printf("q: quit program\n");
	    	printf("i: show help\n");
	    	printf("?: show help\n");
	    	printf("<enter>: show next line\n");
	    	printf("---wasd---\n");
	    	printf("w: show prev line\n");
	    	printf("a: show prev char\n");
	    	printf("s: show next line\n");
	    	printf("d: show next char\n");
	    	printf("---hjkl---\n");
	    	printf("h: show prev char\n");
	    	printf("j: show next line\n");
	    	printf("k: show prev line\n");
	    	printf("l: show next char\n");
	  		break;
	  	case QUIT:
		    printf("unlocking file pid=%d\n", pid);
		    retcode = flock(f, LOCK_UN);
		    handle_error(retcode, "flock LOCK_UN", PROCESS_EXIT);
		    printf("unlocked file pid=%d\n", pid);
	  	  printf("\nexit program, BYE\n");
	  	  close(f);
			  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
				/* code */
				return 0;
	  	case NEXT:
	  	case NEXTLINE:
		  	while(1)
	    	{
	    		char c;
	    		b = read(f, &c,1);
		    	if (b < 1) {
		      	printf("file finished, nothing to read\n");
		      	break;
		    	}	 
		    	else {
		    		printf("%c", c);
		    	}  
		    	if (c == '\n'
		    	 || key == NEXT) {
	    			fflush(stdout);
		    		break;
		    	}
		  	}
	  	  break;
	  	case PREV:
	  	case PREVLINE:
		  	while(1)
	    	{
	    		off_t filepos;
					filepos = lseek(f, 0, SEEK_CUR);
					if (filepos < 2)
					{
						printf("cursor is on the first position\n");
		    		fflush(stdout);
						break;
					}
					else
					{
			  		pos = lseek(f, (-2), SEEK_CUR);
		    		char c;
		    		b = read(f, &c,1);
			    	if (b < 1) {
			      	printf("file finished, nothing to read\n");
			      	break;
			    	}	 
			    	else {
			    		printf("%c", c);
			    	}  
			    	if (c == '\n'
			    	 || key == PREV) {
		    			fflush(stdout);
			    		break;
			    	}
			    }
		  	}
	  		break;
	  	default:
	  		break;
	  }

  }

  printf("unlocking file pid=%d\n", pid);
  retcode = flock(f, LOCK_UN);
  handle_error(retcode, "flock LOCK_UN", PROCESS_EXIT);
  printf("unlocked file pid=%d\n", pid);

  close(f);
  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
	/* code */
	return 0;
}