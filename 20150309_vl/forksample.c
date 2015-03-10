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

	ppid = getpid();
	printf("PID: %d - %s\n", ppid, "before fork" );

	if ((cpid = fork()) < 0) {
		err_sys("fork error");
	}

	pid = getpid();
	printf("Afterfork\n PID: %d\n PPID: %d\n CPID: %d\n", pid, ppid, cpid);

	if (cpid > 0) {
		// parent section 
		// do parent specific stuff
		//exit(0);
	} else {
		// child section -> cpid = 0
		// do child specific stuff
		//exit(0);	
	}

	// common section
	printf("PID: %d - %s\n",pid, "before exit main" );
	exit(0);
}

