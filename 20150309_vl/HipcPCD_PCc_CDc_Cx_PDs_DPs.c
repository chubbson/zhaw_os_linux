/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri
 * Date: 2014-03-01p
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

//daeomnize-group-signal.c

#include <apue.h>
#include <itskylib.h>
#include <kb.h>
#include <tell_wait.h>

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

	TELL_WAIT(); // set things up for tell & wait

	ppid = getpid();

	//generate child
	if ((cpid = fork()) < 0) 
		err_sys("fork error");

	pid = getpid();
	//printf("Afterfork\n PID: %d\n PPID: %d\n CPID: %d\n", pid, ppid, cpid);

	if (cpid > 0) { 
		printf("PID: %d - Parent\n", pid);
		// parent section 

		// wait till child finished
		printf("PID: %d - sending sig from parent\n", pid);
		fflush(stdout);
		TELL_CHILD(pid);

		WAIT_CHILD(); //
		printf("PID: %d - received sig from grandchild\n", pid);
		fflush(stdout); 

		// send daemon a signal 

		// wait for signal of daemon
		//exit(0);
	} else { 
	  // child section -> cpid = 0
		//printf("Afterfork chlid\n PID: %d\n PPID: %d\n CPID: %d\n", pid, ppid, cpid);
		//exit(0);	

		// send signal to parent
			printf("PID: %d - sending sig from grandchild\n", getpid());
		fflush(stdout);
			TELL_PARENT(getpid()); // tell parent we're done

					// receive signal from parent
			WAIT_PARENT(); // 
			printf("PID: %d - received sig from parent\n", getpid());
		fflush(stdout);

			


		// generate daemon
		if((cpid = fork()) < 0)
			err_sys("fork error");

		pid = getpid();
		//printf("AfterGrandchildfork parent\n PID: %d\n PPID: %d\n CPID: %d\n", pid, ppid, cpid);

		if (cpid > 0) {
			// child section
			printf("PID: %d - Child\n", pid);


			exit(0);
		} else {
			// grandchild section, aka daemon
			printf("PID: %d - GrandChild\n", pid);

			// exit grandchild
			exit(0);
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
