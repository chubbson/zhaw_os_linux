/* (C) IT Sky Consulting GmbH 2014
 * http://www.it-sky-consulting.com/
 * Author: Karl Brodowsky
 * Date: 2014-02-27
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
 *
 * create a process
 */

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "include/errorhandler.h"

DWORD WINAPI MyThreadFunction(LPVOID param);

int main(int argc, char *argv[]) {

  printf("in create-thread\n");

  HANDLE threadHandle;
  DWORD threadId;
  int c = 7; 

  printf("argc: %d\n", argc);

  threadHandle = CreateThread(NULL, /* LPSECURITY_ATTRIBUTES lpThreadAttributes, */
                               0, /* SIZE_T dwStackSize, */
                               MyThreadFunction, /* LPTHREAD_START_ROUTINE lpStartAddress, */
                               &c, /* LPVOID lpParameter, */
                               0, /* DWORD dwCreationFlags, */
                               &threadId); /* LPDWORD lpThreadId */
  printf("thread created threadId=%d\n", threadId);
  Sleep(3000);
  printf("ending thread from parent\n");
  TerminateThread(threadHandle, 0);
  printf("terminated thread\n");
  Sleep(3000);


  printf("done with create-thread\n");

  ExitProcess(0);
}


DWORD WINAPI MyThreadFunction(LPVOID param) {
  printf("in thread\n");
  DWORD * idxPtr = (DWORD *) param;
  DWORD idx = *idxPtr;  
  printf("%s\n", (int) idx);
  Sleep(5000);
  printf("done with thread\n");
  return 0;
}
