#include <windows.h>
#include <string.h>
#include "include/errorhandler.h"

typedef struct {
  PROCESS_INFORMATION processInformation;
  STARTUPINFO startupInfo;
} procstruct;

int main(int argc, char *argv[]) {
  BOOL result;

  procstruct procs[5];
  char argvchild[100];
  int pid = _getpid();

  printf("(%d)\tcreate-process START argc:%d\n", pid, argc);

  strcpy(argvchild, "h1");
  for (int i = 1; i < argc; ++i)
  {
    strcat(argvchild, " ");
    strcat(argvchild, argv[i]);
  }

  for (int i = 0; i < 5; ++i)
  {
    GetStartupInfo(&procs[i].startupInfo);
    result = CreateProcess("h1.exe",//"create-thread.exe", /* LPCTSTR lpApplicationName, */
                            argvchild,//(argc > 1) ? "h1.exe 0" : "", /* LPTSTR lpCommandLine, */
                            NULL, /* LPSECURITY_ATTRIBUTES lpProcessAttributes, */
                            NULL, /* LPSECURITY_ATTRIBUTES lpThreadAttributes, */
                            FALSE, /* bInheritHandles, */
                            CREATE_NEW_CONSOLE, // 0, /* CREATE_NEW_CONSOLE,  DWORD dwCreationFlags, */
                            NULL, /* LPVOID lpEnvironment, */
                            NULL, /* LPCTSTR lpCurrentDirectory,*/
                            &procs[i].startupInfo, /* LPSTARTUPINFO lpStartupInfo, */
                            &procs[i].processInformation); /* LPPROCESS_INFORMATION lpProcessInformation */
  }
  printf("in parent process\n");
  Sleep(3000);
  for (int i = 0; i < 5; ++i)
  {
    printf("terminating child %d\n", i);
    TerminateProcess(procs[i].processInformation.hProcess, 0);
    printf("child terminated %d\n", i);
    Sleep(1000);
  }

  ExitProcess(0);
}

