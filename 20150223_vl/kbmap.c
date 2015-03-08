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
// fifo as file in stream
// or file as argument.
// check args. 
// check if is file ...
int main(int argc, char const *argv[])
{
	const char *FILENAME = "out-lowlevel.txt";

/*
	if(argc )


	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0) {
			err_ret("lstat error");
			continue;
		}
		if (S_ISREG(buf.st_mode))
			ptr = "regular";
		else if (S_ISDIR(buf.st_mode))
			ptr = "directory";
		else if (S_ISCHR(buf.st_mode))
			ptr = "character special";
		else if (S_ISBLK(buf.st_mode))
			ptr = "block special";
		else if (S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		else if (S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		else if (S_ISSOCK(buf.st_mode))
			ptr = "socket";
		else
			ptr = "** unknown mode **";
		printf("%s\n", ptr);
	}
*/
  char line[MAXLINE];

  int f = open(FILENAME, O_RDONLY, 0666);
  handle_error(f, "fopen", PROCESS_EXIT);
  int pid = getpid();



  // try non-blocking-lock 
  int retcode, n;

  // trying shared lock 
  n = sprintf(line, "%s%d\n" ,"trying to lock (sh) file pid=", pid);
  write(STDOUT_FILENO, line, n);
  //int l = strlen(line);
  //printf("n: '%d' l: '%d' m; #%s#", n, l, line);

  //write(STDOUT_FILENO,"=====HELP=====\n",15);
  retcode = flock(f, LOCK_SH); 
  handle_error(retcode, "flock LOCK_SH", PROCESS_EXIT);

  n = sprintf(line, "locked (ex) file pid=%d\n", pid);
  write(STDOUT_FILENO ,line, n);

  //printf("locked (ex) file pid=%d\n", pid);
	//fflush(stdout);

	char buf[2];
	int b;
 
	while((n = read(STDIN_FILENO, buf, 1)) > 0)
	{
		buf[n] = 0; /* null terminate*/
/*		printf("n:%d - '%s'\n",n , buf);
		printf("strlen: '%d'\n", strlen(buf));
		fflush(stdout);
*/
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
			  n = sprintf(line, "unlocking file pid=%d\n", pid);
  			write(STDOUT_FILENO ,line, n);

		    //printf("unlocking file pid=%d\n", pid);
		    retcode = flock(f, LOCK_UN);
		    handle_error(retcode, "flock LOCK_UN", PROCESS_EXIT);

			  n = sprintf(line, "unlocked file pid=%d\n", pid);
  			write(STDOUT_FILENO ,line, n);
		    //printf("unlocked file pid=%d\n", pid);
	    	//write(STDOUT_FILENO,"\nexit program, BYE\n",18);
			  n = sprintf(line, "\nexit program, BYE\n");
  			write(STDOUT_FILENO ,line, n);

	    	//printf("\nexit program, BYE\n");
	    	fflush(stdout);
	  	  close(f);
			  return 0;
	  	case NEXT:
	  	case NEXTLINE:
		  	while(1)
	    	{
	    		char c;
	    		b = read(f, &c,1);
		    	if (b < 1) {
		    		n = sprintf(line, "file finished, nothing to read\n");
  					write(STDOUT_FILENO ,line, n);
		      	break;
		    	}	 
		    	else {
		    		n = sprintf(line, "%c", c);
  					write(STDOUT_FILENO ,line, n);
		    	}  
		    	if (c == '\n'
		    	 || key == NEXT) {
//	    			fflush(stdout);
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
		    		n = sprintf(line, "cursor is on the first position\n");
  					write(STDOUT_FILENO ,line, n);
//		    		fflush(stdout);
						break;
					}
					else
					{
			  		filepos = lseek(f, (-2), SEEK_CUR);
		    		char c;
		    		b = read(f, &c,1);
			    	if (b < 1) {
			    		n = sprintf(line, "file finished, nothing to read\n");
	  					write(STDOUT_FILENO ,line, n);
			      	break;
			    	}	 
			    	else {
			    		n = sprintf(line, "%c", c);
	  					write(STDOUT_FILENO ,line, n);
//			    		printf("%c", c);
			    	}  
			    	if (c == '\n'
			    	 || key == PREV) {
		    			fflush(stdout);
			    		break;
			    	}
			    }
		  	}
	  		break;
	  	//case NONE: 
	  	//	printf("switch case none\n");
	  		//fflush(stdout);
	  		break;
	  	default:
    		n = sprintf(line, "switch case default\n");
				write(STDOUT_FILENO ,line, n);
//	  		printf("switch case default\n");
	  	//flush(stdout); 
	  		break;
		}
		//fflush(STDOUT_FILENO);
	  fflush(stdout); 
	}

	n = sprintf(line, "unlocking file pid=%d\n", pid);
	write(STDOUT_FILENO ,line, n);

  //printf("unlocking file pid=%d\n", pid);
  retcode = flock(f, LOCK_UN);
  handle_error(retcode, "flock LOCK_UN", PROCESS_EXIT);

  n = sprintf(line, "unlockied file pid=%d\n", pid);
	write(STDOUT_FILENO ,line, n);
  //printf("unlocked file pid=%d\n", pid);

  close(f);
	/* code */
	return 0;
}