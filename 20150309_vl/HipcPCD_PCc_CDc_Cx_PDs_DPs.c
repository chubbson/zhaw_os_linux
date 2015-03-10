/* (C) Hauronen Patronens waste of time projects!
* https://github.com/chubbson/zhaw_os_linux
* Author: David Hauri
* Date: 2014-03-01p
* License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
*/

//daeomnize-group-signal.c

#include <apue.h>
#include <itskylib.h>
#include <kb.h>

static void sig_handler(int); // signal handler
static void sig_handlerChild(int); // signal handler
static void sig_handlerAlarm(int); // signal handler

// HipcPCD_PCc_CDc_Cx_PDs_DPs.c
// H = HomeWork
// ipc = interprocess Communication
// PCD = Parent Child Daemon
// PCc = Parent create Child
// CDc = Child create Daemon 
// Cx = Exit Child
// PDs = Parent send sig to Daemon 
// DPs = Daemon send sig to Parent
int main(int argc, char const *argv[])
{
	pid_t pid, ppid, cpid;
//	char line[MAXLINE];
/*
	if(signal(SIGINT, sig_handler) == SIG_ERR)
		err_sys("signal error");
*/
	ppid = getpid();
	printf("PID: %d - %s\n", ppid, "before fork" );

	//generate child
	if ((cpid = fork()) < 0) 
		err_sys("fork error");

	pid = getpid();
	printf("Afterfork\n PID: %d\n PPID: %d\n CPID: %d\n", pid, ppid, cpid);

	if (cpid > 0) {
		// parent section 

		// wait till child exits

		// send daemon a signal 
		
		// wait for signal of daemon
		//exit(0);
	} else {
		// child section -> cpid = 0
		//printf("Afterfork chlid\n PID: %d\n PPID: %d\n CPID: %d\n", pid, ppid, cpid);
		//exit(0);	

		// generate daemon
		if((cpid = fork()) < 0)
			err_sys("fork error");

		pid = getpid();
		printf("AfterGrandchildfork parent\n PID: %d\n PPID: %d\n CPID: %d\n", pid, ppid, cpid);

		if (cpid > 0) {
			// child section
			// daemon created, exit child
			exit(0);
		} else {
			// grandchild section, aka daemon

			// send signal to parent

			// receive signal from parent

			// exit grandchild
		}
		// common child and grandchild section but grandchild already exits, so just common child section

		// exit 
	}

	// wait till child exit

	// send signal 
	// common section parent, child
	printf("PID: %d - %s\n",pid, "before exit main" );
	exit(0);
}
/*
static void sig_handler(int signo)
{
   printf("Caught signal %d, coming out...\n", signo);
   fflush(stdout);
   //exit(1);
}

static void sig_handlerChild(int signo)
{
	printf("caught signal %d with sig_handlerChild", signo);
}

static void sig_handlerAlarm(int signo)
{
	printf("caught alarm signal %d with sig_handlerAlarm", signo);
}
*/
