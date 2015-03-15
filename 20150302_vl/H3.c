/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri
 * Date: 2014-03-14
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

/*
 * H3 (2015-03-02):
 * worked at from 2015-03-14 1600 - 2015-03-15 2000
 * Write a program that starts a daemon process for calculating squares:
 * main forks child
 * child forks daemon
 * child ends itself
 * parent observes termination of child
 * a named pipe is used to communicate from parent to daemon that child has ended (for example by sending an "S" for "start")
 * the same named pipe can then be used to send numbers to the daemon
 * it will write the squares of the numbers to a file (or another named pipe) given on the command line
 * sending "Q" or "QUIT" terminates the daemon
 * other non-numberic messages are ignored
**/

#include <apue.h>
#include <itskylib.h>
#include <fcntl.h>
#include <read_line.h>
#include <somecolor.h>

 #define FILENAME "test.txt"
 #define TEMPFIFO "temp.fifo"

enum daemon_action { START, QUIT, NUMBER, DROP };
static void charatime(char *);
int daemonized = FALSE;


int formattedpids2buf(char * buf){
	int pid = getpid();
  int pgid = getpgid(pid);
  int ppid = getppid();
  int n = sprintf(buf, "pid=" KBBLU " '%d' " RESET 
  	                  "pgid=" KBRED " '%d' " RESET 
  	                  "ppid=" KYEL  " '%d' " RESET, pid, pgid, ppid);
  buf[n] = '\0';
  return n; 
}

void printPids(char * piddesc) {
  char buf[MAXLINE]; 
  int n = formattedpids2buf(buf);
  // small array excourse, just wanna know if it works that that way
  // i know its ugly :)  
  // cant use n cuz of these color string thing haha :) but 42 seems the answer of .... 
  n = 42; 
  char cdyn[n*2+2]; 
  cdyn[n] = '\0';
  cdyn[n*2+1] = '\0';
  memset(&(cdyn[0]), (int)'-', n);
  memset(&(cdyn[n+1]), (int)'=', n);

  printf("%s\n", cdyn);
 // printf("%s\n", cdyn[43]);

  printf(BLKBLDBLURED "%s" RESET "\n" 
  	     BLKBLDBLURED "+" RESET KBBLU " %s\n"
  	     BLKBLDBLURED "+" RESET " %s\n" 
  	     BLKBLDBLURED "%s" RESET "\n", cdyn, piddesc, buf, &(cdyn[43]));
}

void signal_handler(int signo) {
	daemonized = TRUE;
  char buf[MAXLINE]; 
  /*int n = */formattedpids2buf(buf);
  printf("signal " KGRN "%d" RESET " received %s\n", signo, buf);
}

void printHelp()
{
	printf(RESET KBRED    "*************************************"
		     RESET KYEL   "\n i, h, ?\t\t" RESET "- HELP"
		     RESET KBYEL  "\n s, start\t" RESET "- Start write fifo"
		     RESET KBCYN  "\n q, quit\t\t" RESET "- Exit program"
		     RESET KBMAG  "\n <number>\t" RESET "- stores square in given file / pipe"
		     RESET KBRED  "\n#####################################" RESET "\n"
		           );
}

int main(int argc, char *argv[])
{
	pid_t pid, pgid, ppid; 
	int status, retcode; 
	int fdread, fdwrite;

	if (argc != 2)
		err_quit("usage: %s <restofile>", argv[0]);

  pid = getpid();
  pgid = pid;
  /* set pgid to pid */
  retcode = setpgid(pid, pgid);
  handle_error(retcode, "setpgid", PROCESS_EXIT);

  unlink(TEMPFIFO);
  // create the FIFO (named pipe) 
  //0777
  retcode = mkfifo(TEMPFIFO, 0777);
	handle_error(retcode, "mkfifo", PROCESS_EXIT);
	if((fdread = open(TEMPFIFO, O_RDONLY | O_NONBLOCK)) < 0)
		handle_error(fdread, "open read", PROCESS_EXIT);
	if((fdwrite = open(TEMPFIFO, O_WRONLY)) < 0)
		handle_error(fdread, "open write", PROCESS_EXIT);

	signal(SIGUSR1, signal_handler);


	ppid = pid;
	// * main forks child
	if ((pid = fork()) < 0){
		err_sys("fork error");
	} else if (pid == 0) {
		// Child tell parent

		pid = getpid();
 	  int rootpgid = pid;
  	/* set pgid to pid */
  	retcode = setpgid(pid, rootpgid);

		printPids("Child");

		// * child forks daemon
		if((pid = fork()) < 0){
			err_sys("fork (2) error");
	  } else if (pid != 0) {
	  	// child section

      // * exit child, make grand child a daemon 
			charatime("output from child\n");
      printf("exiting child in 2s\n");
      sleep(2);
      // * child ends itself
      exit(0);
    } else {
			printPids("Grand-Child");
		 // signal(SIGUSR1, signal_handler);

      int i = 0;
			// wait till grand child is daemonized, abort after 5 tries
			while (!daemonized && (i++) < 5) {
				printf("Grand-Child is not daemonized, sleep 1s\n");
	  	  sleep(1);
	  	}

      printf("Grand-Child daemonized, sleep 2s before reading fifo\n");
      sleep(2);

      FILE *fpout; 
		  FILE *fp_fifo;

		  // READING PART - daemonized grand child
		  int n = 0; 
		  char buf[MAXLINE];

		  if((fp_fifo = fdopen(fdread, "r")) == NULL)	
		  	err_sys("fdopen error");

		  printHelp();

			int doQuit = FALSE;
			int isStarted = FALSE;
			for (;;) {
   			while (fgets(buf, sizeof buf, fp_fifo) != NULL && !doQuit)
   			{   				
   				// replace newline with string terminator
	        if(buf[(n=strlen(buf)-1)] == '\n')
   					buf[n] = '\0';

					int nbr; 
   				enum daemon_action dact;
				  if (strcmp(buf,"q") == 0 || strcmp(buf,"Q") == 0 || strcmp(buf,"QUIT") == 0) {
				    dact = QUIT;
				  } else if (strcmp(buf,"s") == 0 || strcmp(buf,"S") == 0 || strcmp(buf,"START") == 0) {
				    dact = START;
				  } else if ((nbr = atoi(buf)) != 0) {
				    dact = NUMBER;
				  } else {
				  	dact = DROP;
				  }
				  printf("enum: %d - %s\n", dact, buf);
    		  //continue;
				  switch(dact){
				  	case QUIT:
				  		if(isStarted && !doQuit && (retcode = fclose(fpout)) != 0)
					  		err_sys("fclose error");

				  		doQuit = TRUE;
				  		printf("%s\n", "QUIT");
				  		break;
				  	case START:
				  		if(!isStarted && (fpout = fopen(argv[1], "wb")) == NULL)
								err_sys("can't open %s", argv[1]);

				  		isStarted = TRUE;
				  		printf("%s\n", "START");
				  		break;
				  	case NUMBER:
				  		printf("%s - started: %d\n", "NUMBER", isStarted);
				  	  if(!isStarted)
				  	  	continue;
				  	  fprintf(fpout, "%d\n", nbr*nbr);
				  	  //sprintf("%d\n", nbr*nbr);
				  		printf("%s: %d\n", "NUMBER", nbr);
				  		break;
				  	case DROP:
				  	default:
				  		printf("%s: \n", "Dropped msg");
			    		continue;
				  		break;
					}	        
   			}
   			if (doQuit == TRUE)
   				break;
      }

      printf("%s\n","reader finished" );

		  fclose(fp_fifo);
		  // fdread must not be closed, this should be done by fclose(fp_fifo) via fdopen(fdread)
		  close(fdwrite);


		  printf("Grand-Child closes in 2s\n");

			sleep(2);

			exit(0);
    }


	} else {
		printPids("Parent");
		// parent
		// * parent observes termination of child
		printf("parent waiting for child\n");
		retcode = wait(&status);
	  handle_error(retcode, "wait", PROCESS_EXIT);
	  printf("child terminated status=%d\n", status);
	  
	  printf("%s%d\n", "pgid grant-(child): ", -pid);
	  // pid is pid of exited child which defined it as pgid for child an grandchild
	  retcode = kill(-pid, SIGUSR1);
	  handle_error(retcode, "kill sigusr1", PROCESS_EXIT);
 

		int fd_fifo = fdwrite;
	  char line[MAXLINE];
		int n = 0; 

		while (fgets(line, MAXLINE, stdin) != NULL){
			n = strlen(line);
			if(write(fd_fifo, line, n) != n)
				err_sys("write error to named pipe");
			if(line[n-1] == '\n')
				line[n-1] = '\0';
			if(strcmp(line, "q") == 0 || strcmp(line, "Q") == 0 || strcmp(line, "QUIT") == 0 )
				break;
		}

    printf("%s\n", "after close before exit");

    printf("%s\n", "after fclose");
	  printf("sadf %s\n", "parent finished in 10s");

	  sleep(10);
	}	


	//clr_f1(fdread, O_NONBLOCK);
	
	exit(0);
}


static void charatime(char *str) {
	char *ptr;
	int c; 
	setbuf(stdout, NULL);
	for(ptr = str; (c = *ptr++) != 0;)
		putc(c, stdout);
}
