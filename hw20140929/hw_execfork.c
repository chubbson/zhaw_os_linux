#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdlib.h> // Declaration for exit();
#include <string.h> // used for strcat
//#include <iostream>


int globalVariable = 2;

main(int argc, char * argv[])
{
  int opt, eflag = 0;

  while ((opt = getopt(argc, argv, "eE")) != -1)
  {
      switch (opt)
      {
        case 'e':
        case 'E':
            eflag = 1;
            break;
        default:
            eflag = 0;
      }
  }

  printf("eflag: %d \n", eflag);

  // start programm
  // Thema: Fork / Exec 
  // Vorleseung: 4/5?
  // Based on www.yolinux.com/tutorials/forkExecProcesses.html
  int iStackVariable = 20; 

  pid_t pID = getpid();
  pid_t fpID;
  int status;


  char sIdentifier_[100];
  strcpy(sIdentifier_, "pID");
  strcat(sIdentifier_, ": ");
  printf("%s %d \n", sIdentifier_, pID);

  printf("Process till Fork \n");
  printf("Process new Orig as parent with pID+1 till end \n");
  printf("Process fork with pId=0 uses memory form Parent \n");
  

  if((fpID = fork()) == 0)
  {
    printf("Childproc calling sleeptest \n");
    // the child process
    //sleeptest
    switch (eflag)
    {
      case 1: 
        execl("./sleep_ex","./sleep_ex","1", NULL);
        break;
      default: 
        execl("./sleep_ex","./sleep_ex", NULL);
        break;
    }
    // if execl() was successful, this won't be reached.
    printf("if execl was successfull this wont be reached -> call _exit(127)");
    _exit(127);
  } 

  if (fpID > 0)
  {
    printf("Parentproc calls waitpid\n");
    // the parent process calls waitpid() on the child
    if(waitpid(fpID, &status, 0) > 0)
    {
      if(WIFEXITED(status) && !WEXITSTATUS(status))
      {
        printf("The program terminated normally and executed successfully \n");
      }
      else if (WIFEXITED(status) && WEXITSTATUS(status))
      {
        if (WEXITSTATUS(status) == 127) 
        {
          printf("Execl() failed \n");
        }
        else
        {
          // the programm terminated normally, but returen a non-zero status
          switch (WEXITSTATUS(status)) 
          {
            // handle each particular return code that the programm can return
            //case 1:
            //  statements
            //break;
            default:
              printf("Program terminated normally with unhandled exit code: %d \n", status);
          }
        }
      }
    }
    else 
    {
      printf("waitpid() failed \n");
    }
  }
  else
  {
    printf("failed to fork()");
  }
   
  exit(0);
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
