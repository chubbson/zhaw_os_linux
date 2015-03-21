/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri
 * Date: 2015-03-16
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

/**
 * Coprocessore sample
**/

#include <apue.h>
#include <itskylib.h>
#include <fcntl.h>
#include <read_line.h>
#include <somecolor.h>
#include <coproc.h>

static void charatime(char *);
static void	sig_pipe(int);		/* our signal handler */

int daemonized = FALSE;
enum daemon_action { START, QUIT, NUMBER, DROP, INFO };


int formattedpids2buf(char * buf){
	int pid = getpid();
  int pgid = getpgid(pid);
  int ppid = getppid();
  int n = sprintf(buf, "pid=" KBBLU " '%d' " RESET 
  	                  "pgid=" KBRED " '%d' " RESET 
  	                   "ppid=" KYEL " '%d' " RESET, pid, pgid, ppid);
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
  formattedpids2buf(buf);
  printf("signal " KGRN "%d" RESET " received %s\n", signo, buf);
}

int main(int argc, char *argv[])
{
	pid_t pid;//, pgid, ppid; 
	int retcode; 

	if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
		err_sys("signal error");

	//fd1[0] = FD_CHILD_READ;
	//fd1[1] = FD_PARENT_WRITE;
	//fd2[0] = FD_PARENT_READ;
	//fd2[1] = FD_CHILD_WRITE;

  // pipes for parent to write and read
	if (pipe(pipes[PARENT_READ_PIPE]) < 0 
	 || pipe(pipes[PARENT_WRITE_PIPE]) < 0)
		err_sys("pipe error");

  if ((pid = fork()) < 0){
		err_sys("fork error");
	} else 	if (pid == 0) {
		charatime("child section");
		// child section 

		close(FD_PARENT_WRITE);
		close(FD_PARENT_READ); 

		if (FD_CHILD_READ != STDIN_FILENO){
 			if ((retcode = dup2(FD_CHILD_READ, STDIN_FILENO)) != STDIN_FILENO)
				handle_error(retcode, "dup2 error to stdin", PROCESS_EXIT);
			close(FD_CHILD_READ);
		}

		if (FD_CHILD_WRITE != STDOUT_FILENO) {
			if((retcode = dup2(FD_CHILD_WRITE, STDOUT_FILENO)) != STDOUT_FILENO)
				handle_error(retcode, "dup2 error to stdout", PROCESS_EXIT);
			close(FD_CHILD_WRITE);
		}
		
    if (execl("./kbfilter", "kbfilter", (char *)0) < 0)
			err_sys("execl error");
 	} else {
		charatime("parent section");
		// parent section
	  char line[MAXLINE];
		int n;

		close(FD_CHILD_READ);
		close(FD_CHILD_WRITE);

		while (fgets(line, MAXLINE, stdin) != NULL) {
			n = strlen(line);
			if (write(FD_PARENT_WRITE, line, n) != n)
				err_sys("write error to pipe");
			if ((n = read(FD_PARENT_READ, line, MAXLINE)) < 0)
				err_sys("read error from pipe");
			if (n == 0) {
				err_msg("child closed pipe");
				break;
			}
			line[n] = 0;	/* null terminate */
			if (fputs(line, stdout) == EOF)
				err_sys("fputs error");
		}

		if (ferror(stdin))
			err_sys("fgets error on stdin");
		exit(0);
	}
	
	exit(0);
}


static void charatime(char *str) {
	char *ptr;
	int c; 
	setbuf(stdout, NULL);
	for(ptr = str; (c = *ptr++) != 0;)
		putc(c, stdout);
}

static void sig_pipe(int signo) {
	printf("SIGPIPE caught\n");
	exit(1);
}
