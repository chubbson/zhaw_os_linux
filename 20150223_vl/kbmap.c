/* (C) Hauronen Patronens waste of time projects!
* https://github.com/chubbson/zhaw_os_linux
* Author: David Hauri
* Date: 2014-03-01
* License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
*/

#include <fcntl.h>

#include <apue.h>
#include <itskylib.h>
#include <kb.h>

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

	char buf[2];
	int n,b, pos;

	while((n = read(STDIN_FILENO, buf, 2)) > 0)
	{
		buf[n] = 0; /* null terminate*/
		char inkey = buf[0];

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

		//if(write(STDOUT_FILENO, buf, 1) != n)
		//	err_sys("write error");

		switch(key){
	  	case HELP:
	  	  write(STDOUT_FILENO,"=====HELP=====\n",15);
	  	  write(STDOUT_FILENO,"q: quit program\n",16);
	    	write(STDOUT_FILENO,"i: show help\n",13);
	    	write(STDOUT_FILENO,"?: show help\n",13);
	    	write(STDOUT_FILENO,"<enter>: show next line\n",24);
	    	write(STDOUT_FILENO,"---wasd---\n",11);
	    	write(STDOUT_FILENO,"w: show prev line\n",18);
	    	write(STDOUT_FILENO,"a: show prev char\n",18);
	    	write(STDOUT_FILENO,"s: show next line\n",18);
	    	write(STDOUT_FILENO,"d: show next char\n",18);
	    	write(STDOUT_FILENO,"---hjkl---\n",11);
	    	write(STDOUT_FILENO,"h: show prev char\n",18);
	    	write(STDOUT_FILENO,"j: show next line\n",18);
	    	write(STDOUT_FILENO,"k: show prev line\n",18);
	    	write(STDOUT_FILENO,"l: show next char\n",18);
	  		break;
	  	case QUIT:
		    printf("unlocking file pid=%d\n", pid);
		    retcode = flock(f, LOCK_UN);
		    handle_error(retcode, "flock LOCK_UN", PROCESS_EXIT);
		    printf("unlocked file pid=%d\n", pid);
	    	//write(STDOUT_FILENO,"\nexit program, BYE\n",18);
	    	printf("\nexit program, BYE\n");
	  	  close(f);
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
		//fflush(STDOUT_FILENO);
	}

  printf("unlocking file pid=%d\n", pid);
  retcode = flock(f, LOCK_UN);
  handle_error(retcode, "flock LOCK_UN", PROCESS_EXIT);
  printf("unlocked file pid=%d\n", pid);

  close(f);
	/* code */
	return 0;
}