/* (C) Hauronen Patronens waste of time projects!
* https://github.com/chubbson/zhaw_os_linux
* Author: David Hauri
* Date: 2014-03-01
* License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
*/
#include <apue.h>
#include <itskylib.h>
#include <kb.h>

static void sig_pipe(int); // signal handler
static struct termios orig_termios_struct;

int main(int argc, char const *argv[])
{
	char c; 
	int n, fd1[2], fd2[2];
	pid_t pid;
	char buf[2];
	char line[MAXLINE];

	printf("%s\n", "kbin start" );

	if(signal(SIGPIPE, sig_pipe) == SIG_ERR)
		err_sys("signal error");

	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		err_sys("pipe error");


	printf("%s\n", "before fork" );
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	}
	else if (pid > 0) {
	// parent
		close(fd1[0]);
		close(fd2[1]);

		printf("PID: %d - %s\n",pid, "After fork parent" );
		fflush(stdout);

		struct termios termios_struct;

	  tcgetattr(STDIN_FILENO, &orig_termios_struct);
	  tcgetattr(STDIN_FILENO, &termios_struct);
	  // could be done like this also:
	  // termios_struct = orig_termios_struct;

	  termios_struct.c_lflag &= (~ICANON) & (~ECHO);
	  termios_struct.c_cc[VTIME] = 0;
	  termios_struct.c_cc[VMIN] = 1;
	  tcsetattr(STDIN_FILENO, TCSANOW, &termios_struct);
	  sleep(1);
/*
	  if (setvbuf(stdin,NULL,_IOLBF,0) != 0)
	  {
	  	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
	  	err_sys("setvbuf error");
	  }
	  if (setvbuf(stdout,NULL,_IOLBF,0) != 0)
	  {
	  	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
	  	err_sys("setvbuf error");
	  }

	  */
	  /*
	  while(fgets(line, MAXLINE, stdin) != NULL)
	  {
	  	n = strlen(line);
	  	if(write(fd1[1], buf, n) != n)
			{
	  		tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
				err_sys("write error to pipe");
			} else { printf("written bytes: %d\n", n); fflush(stdout);}
			if ((n = read(fd2[0], line, MAXLINE)) < 0)
		  {
		  	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
				err_sys("read error from pipe");
			} else { printf("read bytes: %d\n", n); fflush(stdout);}
			if(n==0) {
	  		tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
				err_msg("child closed pipe");
				break;
			}
			line[n] = 0; // null terminate
			if(fputs(line, stdout) == EOF)
			{
		  	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
				err_sys("fputs error");	
			}
		}
		
		tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);

		if(ferror(stdin))
				err_sys("fgets error on stdin");
		exit(0);

		
			printf("PID: %d, line: #%s# lenght: %d \n", pid, line, n); fflush(stdout);
			write(STDOUT_FILENO, line, n);

	  }
	  while(1)
		*/
	  while((c = getc(stdin)) != EOF)
		//while(fgets(line, MAXLINE, std)n > 2014-03-01)
		{
			//c = getchar();
			//n = strlen(line);
			//printf("fgets line: %d, %s, %d\n", pid, line, n); fflush(stdout);
			n = 1;
			buf[0] = c;
			buf[1] = 0;
			printf("PID: %d, %s, %d\n", pid, buf, n); fflush(stdout);

			if(write(fd1[1], buf, n) != n)
			{
	  		tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
				err_sys("write error to pipe");
			} else { printf("written bytes: %d\n", n); fflush(stdout);}
			if ((n = read(fd2[0], line, MAXLINE)) < 0)
		  {
		  	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
				err_sys("read error from pipe");
			} else { printf("read bytes: %d\n", n); fflush(stdout);}
			if(n==0) {
	  		tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
				err_msg("child closed pipe");
				break;
			}
			line[n] = 0; // null terminate
			printf("PID: %d, line: #%s# lenght: %d \n", pid, line, n); fflush(stdout);
			write(STDOUT_FILENO, line, n);

/*
			// print read stream to output
			if (fputs(line, stdout) == EOF)
			{ tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
				err_sys("fputs error");
			}
*/			//fflush(stdout);
		}
     
  	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);

		if(ferror(stdin))
				err_sys("fgets error on stdin");
		exit(0);
	} else {
	// child
		close(fd1[1]);
		close(fd2[0]);

		printf("PID: %d - %s\n",pid, "After fork Child" );
		fflush(stdout);

		if (fd1[0] != STDIN_FILENO){
			if(dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd1[0]);
		}

		printf("PID: %d - %s\n",pid, "After fd1[0] != STDIN_FILENO" );
		fflush(stdout);

		if (fd2[1] != STDOUT_FILENO){
			if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				err_sys("dup2 error to stdin");
			close(fd2[1]);
		}
		
		printf("PID: %d - %s\n",pid, "After fd2[1] != STDOUT_FILENO" );
		fflush(stdout);

		if(execl("./kbmap","kbmap",(char *)0) < 0)
			err_sys("execl error");
	}
	exit(0);
}

static void sig_pipe(int signo)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios_struct);
	exit(1);
}
