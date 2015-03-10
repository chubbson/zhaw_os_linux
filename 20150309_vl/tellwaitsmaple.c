/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri
 * Date: 2014-03-01p
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/


#include "apue.h"

static void charatime(char *);

int main(void)
{
	pid_t pid; 
	TELL_WAIT();

	if ((pid) = fork() < 0){
		err_sys("fork error");
	} else if (pid == 0) {
		WAIT_PARENT(); // parent goes first
		charatime("output from child\n");
	} else {
		charatime("output from parent\n");
		TELL_CHILD(pid);
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