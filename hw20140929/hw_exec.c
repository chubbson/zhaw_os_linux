#include <stdio.h>
#include <unistd.h>

#include <stdlib.h> // Declaration for exit();
#include <string.h> // used for strcat
//#include <iostream>


int globalVariable = 2;

main()
{
  // start programm
  // Thema: Fork / Exec 
  // Vorleseung: 4/5?
  // Based on www.yolinux.com/tutorials/forkExecProcesses.html
  int iStackVariable = 20; 

  pid_t pID = getpid();

  char sIdentifier_[100];
  strcpy(sIdentifier_, "pID");
  strcat(sIdentifier_, ": ");
  printf("%s %d \n", sIdentifier_, pID);

  int execReturn = 0;


  //execReturn = execl("/bin/ls", "/bin/ls", "-r", "-t", "-l", (char *) 0);
  //execReturn = execl("./sleeptest", (char *) 0);

  char *args[] = { "./hw_fork", (char *) 0 };
  //execReturn = execv("./hw_fork", args);
  //execReturn = execl("./sleeptest", (char *) 0);
  execReturn = execl("./sleeptest", NULL);
  //execReturn = execl("/home/fedora/Music/vl3/sleeptest", (char *) 0);
  
  printf("Before exit, exec return : %d \n", execReturn);
  // Exit the programm cuz it will called again from child. No idea why this happen. 
  //exit(0);
}
