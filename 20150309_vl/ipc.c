// interprocess communication. 
// verschiedene mechanismen. 
// pipes, Files, tcp ip, sockets, memory mapped file, MOM message passing, named pipes anonymouss pipes, 
// message queue, semaphore, shared memori signal, D-Bus
//
// ipc-1.pdf,
// man signal(7)

// fork, von parent -> child ein signal schicken.   

/* (C) Hauronen Patronens waste of time projects!
* https://github.com/chubbson/zhaw_os_linux
* Author: David Hauri
* Date: 2014-03-01
* License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
*/
#include <apue.h>
#include <itskylib.h>
#include <kb.h>

static void sig_handler(int); // signal handler
static void sig_handlerChild(int); // signal handler
static void sig_handlerAlarm(int); // signal handler

int main(int argc, char const *argv[])
{
	pid_t pid;
	char line[MAXLINE];

	if(signal(SIGINT, sig_handler) == SIG_ERR)
		err_sys("signal error");

/*
	while(TRUE)
	{
		sleep(1);
	}
*/
	printf("%s\n", "before fork" );
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	}
	else if (pid > 0) {
		// parent
		int np; 
		printf("PID: %d - %s\n",pid, "After fork parent" );
		fflush(stdout);

		if(signal(SIGINT, sig_handlerChild) == SIG_ERR)
			err_sys("signal error");

		alarm(5);

		while(TRUE)
		{
			np = sprintf(line, "PID: %d, parent, sleep 1s\n", pid);
			write(STDOUT_FILENO, line, np);
			sleep(1);
		}

		exit(0);
	} else {
		// child
		int nc; 		
		printf("PID: %d - %s\n",pid, "After fork child" );
		fflush(stdout);

		if(signal(SIGALRM, sig_handlerAlarm) == SIG_ERR)
			err_sys("signal error");

		while(TRUE)
		{
			//nc = sprintf(line, "PID: %d, child, sleep 1s\n", pid);
			//write(STDOUT_FILENO, line, nc);
			sleep(1);
		}
		
	}
	exit(0);
}

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


//USAGE(ARGV, SIGNO MUST BE < 256);


//parentint retcode = fill(pid, signo
//handle error(retcode "kill" process_);

//ps auxww|grep 2448

// typedef void (*sighandler_t)(int);
// sighandler_t signal(int signum, sighandler_t handler);
// signal(SIGTERM, SIGIGN);

/*
void myHandler(int signo) {
…}
*/

//signal(SIGTERM, myHandler);

//alarm() SIGALARM
// sendet sig in x sek

// msgsnd(id, msg, size, flags)