/* 
 * H7 (2015-04-27)
 * Write a program for MS-Windows (Win32 or Win64) that
 * * opens a file
 * * reads the file
 * * does a sleep of a few seconds
 * * closes the file again.
 * Depending on the command line arguments, the file is opened exclusively or sharable. The actual file 
 *   can be hard coded or preferably be given as command line argument.
 * Run the program multiple times simultanously to see the effect of exclusive and sharable usage of a file.
**/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "include/errorhandler.h"


#define BUF_SIZE10 10



int main(int argc, char *argv[]) {
  BOOL result;
  const char *hc_fileName = "../temp/test-w-twice.txt";
  char *fileName;
  HANDLE fh1, fh2;
  DWORD errorCode;
  DWORD nRead;
  int doContinue; 
  char outbuf[BUF_SIZE10+1]; 
  int pid = _getpid();
  int i = 0; 
  int sharemode = 0; 

  printf("(%d)\th1 START argc:%d\n", pid, argc);
  for (int i = 0; i < argc; ++i)
  {
  	 printf("(%d)\targv[0]=%s\n", pid, argv[i]);
  }
 
  sharemode = (argc > 1 && strcmp(argv[1], "0") == 0) ? 0 : FILE_SHARE_READ;
  fileName = (argc > 2) ? argv[2] : hc_fileName;

  fh1 = CreateFile(fileName,         /* lpName */
                   GENERIC_READ, /* or GENERIC_READ: dwAccess */
                   sharemode, //FILE_SHARE_READ | FILE_SHARE_WRITE, /* share mode: not shared: dwShareMode */
                   NULL, /* lp security attributes (here alway null) */
                   OPEN_EXISTING, /* or CREATE_NEW OPEN_EXISTING, OPEN_ALWAYS, TRUNCATE_EXISTING dwCreate */
                   FILE_ATTRIBUTE_NORMAL, /* or FILE_ATTRIBUTE_READONLY or FILE_FLAGE_DELETE_ON_CLOSE or FILE_FLAG_OVERLAPPED (assync I/O) .... dwAttrAndFlags */
                   NULL); /* hTemplateFile */
  HandleError("fh1=CreateFile(...) -> errorCode=%ld\n", (fh1 == INVALID_HANDLE_VALUE));

  nRead = 0; 
  doContinue = 1; 
  i = 0; 

  while(doContinue == 1)
  {
  	result = ReadFile(fh1,
										  outbuf,
											BUF_SIZE10,
											&nRead,
											NULL);
  	doContinue = (result != FALSE && nRead == BUF_SIZE10) ? 1 : 0; 
  	HandleError("ReadFile(fh1...)", ! result);

  	i++; 
    outbuf[nRead] = '\0';
    printf("(%d)\t[%d]\t%d\t|%s\n", pid, i, nRead, outbuf);
    Sleep(1000);
  }

  result = CloseHandle(fh1);
  HandleError("CloseHandle(fh1)", ! result);

  printf("(%d)\th1 END\n", pid);
  ExitProcess(0);
}