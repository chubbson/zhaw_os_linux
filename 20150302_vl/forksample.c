/* EXERCISES im repo:

H3 (2015-03-02):
Write a program that starts a daemon process for calculating squares:
* main forks child
* child forks daemon
* child ends itself
* parent observes termination of child
* a named pipe is used to communicate from parent to daemon that child has ended (for example by sending an "S" for "start")
* the same named pipe can then be used to send numbers to the daemon
* it will write the squares of the numbers to a file (or another named pipe) given on the command line
* sending "Q" or "QUIT" terminates the daemon
* other non-numberic messages are ignored
*/

/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri
 * Date: 2014-03-14
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/


#include <apue.h>
#include <itskylib.h>

 #define MAX_BUF 1024
 #define FILENAME "test.txt"
 #define TEMPFIFO "temp.fifo"


static void charatime(char *);
int daemonized = FALSE;

void printPids(char * piddesc) {
  int pid = getpid();
  int pgid = getpgid(pid);
  int ppid = getppid();
  printf("----------\n%s\npid=%d pgid=%d ppid=%d\n daemonized: %d\n==========\n", piddesc, pid, pgid, ppid, daemonized);
}


int main(void)
{
	pid_t pid; 
	int i = 0; 
  pid = getpid();


	// * main forks child
	if ((pid = fork()) < 0){
		err_sys("fork error");
	} else if (pid == 0) {
		// Child tell parent
		printPids("Child");
		i = i; 
		printf("child: i: %d\n", i);
		sleep(3);
		//exit(0);
	} else {
		// Parent
		printPids("Parent");
		daemonized = TRUE; 
		i = 5; 
		printf("Parent i: %d\n", i);
		sleep(1);
		//exit(0);
	}	
	
	printf("Common section i: %d\n", i);
	printPids("common section");
	exit(0);
}

static void charatime(char *str) {
	char *ptr;
	int c; 
	setbuf(stdout, NULL);
	for(ptr = str; (c = *ptr++) != 0;)
		putc(c, stdout);
}
