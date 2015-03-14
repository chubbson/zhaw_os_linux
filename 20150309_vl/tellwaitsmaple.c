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
int bla = FALSE;

void printPids(char * piddesc) {
  int pid = getpid();
  int pgid = getpgid(pid);
  int ppid = getppid();
  printf("----------\n%s\npid=%d pgid=%d ppid=%d\n==========\n", piddesc, pid, pgid, ppid);
}

void signal_handler(int signo) {
	daemonized = TRUE;
  int pid = getpid();
  int pgid = getpgid(pid);
  int ppid = getppid();
  printf("signal %d received pid=%d pgid=%d ppid=%d\n", signo, pid, pgid, ppid);
}

int main(void)
{
	pid_t pid;//, ppid; 
	int status, retcode; 
  pid = getpid();
  int pgid = pid;
  /* set pgid to pid */
  retcode = setpgid(pid, pgid);
  handle_error(retcode, "setpgid", PROCESS_EXIT);

	printPids("Parent");
	signal(SIGUSR2, signal_handler);

	//ppid = getpid();
	if ((pid = fork()) < 0){
		err_sys("fork error");
	} else if (pid == 0) {
		// Child tell parent
		printPids("Child");

		int rootPGid = pgid; 
		pid = getpid();
		pgid = pid;
	  retcode = setpgid(pid, pgid);
	  handle_error(retcode, "setpgid", PROCESS_EXIT);


		if((pid = fork()) < 0){
			err_sys("fork (2) error");
	  } else if (pid != 0) {
	  	// child
      /* exit child, make grand child a daemon */
			charatime("output from child\n");
      printf("exiting child in 2s\n");
      sleep(2);
      exit(0);
    } else {
			printPids("Grand-Child");
		  signal(SIGUSR1, signal_handler);
			charatime("output from grand-child\n");

			// wait till grand child is daemonized
			while (! daemonized) {
	  	  pause();
	  	}

			charatime("grand-child daemonized, sleep 5s before sendig SIGUSR2\n");
			sleep(5);

			// do not send -1, it will logoff current user.. dk why?!?
			// sending sigusr2 to rootpgid which is the pgid form parent, so sending sigusr2 to parent
		  retcode = kill(/*-1*/-rootPGid, SIGUSR2);
  		handle_error(retcode, "kill sigusr2", PROCESS_EXIT);

			exit(0);
    }


	} else {
		// parent
		// pid = chlid pid = child groupid
		printf("parent waiting for child\n");
		retcode = wait(&status);
	  handle_error(retcode, "wait", PROCESS_EXIT);
	  printf("child terminated status=%d\n", status);

		printPids("Parent before sending sigusr1 kill to pid which containts pid of child (it doesnt exist anymore, already exited), but pid is pgid of child and grandchild");

	  retcode = kill(-pid, SIGUSR1);
	  handle_error(retcode, "kill sigusr1", PROCESS_EXIT);

	  printf("%s\n", "parent after kill, pause");
	  // could use a neu sig handler with a glob var for this handler to drop other signals, but ... im to lazy ;) 
	  pause();

	  printf("%s\n", "parent pause finished");
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
