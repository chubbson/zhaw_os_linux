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

  printf("Process till Fork \n");
  printf("Process new Orig as parent with pID+1 till end \n");
  printf("Process fork with pId=0 uses memory form Parent \n");
  

  pid_t fpID = fork();

  if(fpID == 0)
  {
    // Code only executed by chlid process
    
    strcpy(sIdentifier_, "Child Pid: ");
    globalVariable++;
    iStackVariable++;
  }
  else if(fpID < 0)
  {
    printf("Faild to fork \n");
    exit(1);
    // Throw exception
  }
  else 
  {
    // Code only executed by parent process;
    strcpy(sIdentifier_, "ParentPid: ");
  }
  printf("\n Orig pID: %d ", pID);
  printf(" sIdentifier %s %d ", sIdentifier_, fpID);
  printf(" GloblVar: %d ", globalVariable);
  printf(" StackVar: %d \n", iStackVariable);

  exit(0);
  
}
