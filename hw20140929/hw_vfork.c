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

  printf("Process till vfork \n");
  printf("Process fork and run as child with pfId = 0 till end \n");
  printf("Process from fork as Parent with pId+1 uses memory from Parent  till end\n");
  printf("Call exit before main end, cuz of some recursive irritating things \n");
  
  pid_t fpID = vfork();

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

  // Exit the programm cuz it will called again from child. No idea why this happen. 
  exit(0);
}
