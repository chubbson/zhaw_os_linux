/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri
 * Date: 2014-03-12
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/


#include <apue.h>
#include <itskylib.h>

static void charatime(char *);
int daemonized = FALSE;

void signal_handler(int signo) {
	daemonized = TRUE;
  int pid = getpid();
  int pgid = getpgid(pid);
  int ppid = getppid();
  printf("signal %d received pid=%d pgid=%d ppid=%d\n", signo, pid, pgid, ppid);
}

int main(void)
{
	pid_t pid, ppid; 
	int status, retcode; 
  pid = getpid();
  int pgid = pid;
  /* set pgid to pid */
  retcode = setpgid(pid, pgid);
  handle_error(retcode, "setpgid", PROCESS_EXIT);

	signal(SIGUSR2, signal_handler);

	printf("Parent PID: %d\n", getpid());
//	TELL_WAIT();

	ppid = getpid();
	if ((pid = fork()) < 0){
		err_sys("fork error");
	} else if (pid == 0) {
		// Child tell parent
		printf("Child PID: %d\n", getpid());

		if((pid = fork()) < 0){
			err_sys("fork (2) error");
	  } else if (pid != 0) {
	  	// child
      /* exit child, make grand child a daemon */
			charatime("output from child\n");
      printf("exiting child\n");
      sleep(2);
      exit(0);
    } else {
			printf("Grand-Child PID: %d\n", getpid());
    	// grant chlid
			//signal(SIGUSR2, signal_handler);
		  signal(SIGUSR1, signal_handler);
			charatime("output from grand-child\n");

			while (! daemonized) {
	  	  pause();
	  	}

			charatime("grand-child daemonized\n");
			sleep(3);

		  retcode = kill(-pgid, SIGUSR2);
  		handle_error(retcode, "kill", PROCESS_EXIT);

			exit(0);
    }


	} else {
		// parent
		// Parent tell child
		charatime("output from parent\n");
	}

	//parent child grand child

	printf("parent waiting for child\n");
	retcode = wait(&status);
  handle_error(retcode, "wait", PROCESS_EXIT);
  printf("child terminated status=%d\n", status);

  retcode = kill(-pgid, SIGUSR1);
  handle_error(retcode, "kill", PROCESS_EXIT);

	exit(0);
}

static void charatime(char *str) {
	char *ptr;
	int c; 
	setbuf(stdout, NULL);
	for(ptr = str; (c = *ptr++) != 0;)
		putc(c, stdout);
}
