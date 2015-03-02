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
	
	FILE *fpin; 

	  	  printf("1\n");
	if((fpin = popen("./kb", "r"))== NULL)
		err_sys("popen error");

	  	  printf("2\n");
	enum kb_binds *key;
	  	  printf("3\n");

	//char linefake[sizeof(enum kb_binds)];
	char linefake[1];
  while (1) {
  	
    // read(fpin, &key, sizeof(enum kb_binds)) != sizeof(enum kb_binds))
    int res = fgets(linefake, 1, fpin);
    if(res != sizeof(enum kb_binds))
			err_sys("read error enum kb_binds %d, %d", res, sizeof(enum kb_binds));

	  	  printf("4\n");
		switch((enum kb_binds)&key){
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
		    printf("unlocking file pid=%d\n", 1234);// pid);
/*		    retcode = flock(f, LOCK_UN);
		    handle_error(retcode, "flock LOCK_UN", PROCESS_EXIT);
		    printf("unlocked file pid=%d\n", pid);
	  	  printf("\nexit program, BYE\n");
	  	  close(f);
			  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
*/				/* code */
				return 0;
	  	case NEXT:
	  	case NEXTLINE:
		  	while(1)
	    	{
/*	    		char c;
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
*/		  	}
	  	  break;
	  	case PREV:
	  	case PREVLINE:
/*	  	while(1)
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
*/	  		break;
	  	default:
	  		break;
	  }
	}

	/* code */
	return 0;
}