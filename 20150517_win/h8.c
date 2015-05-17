/*h8.c
 * Programm für MS-Windows (Kommandozeile)
 * ● Kommandozeilenargumente sind Dateinamen (mit / oder \)
 * ● Für jedes Argument wird ein Thread gestartet, der die Datei liest.
 * ● Es werden shorts (Byte-Paare gelesen) und deren Häufigkeit
 *   gezählt.
 * ● Das wird in Memory-Struktur aggregiert, die mittels mutex, Critical
 *   section, semaphore oder rwlocks gesichert wird.
 * ● Oder mittels Interlocked-Funktionen
 * ● Am Ende wird das Gesamtergebnis ausgegeben. 0-Werte als
 * Häufigkeiten können weggelassen werden.
**/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "include/errorhandler.h"

#define BUF_SIZE1 1
#define BUF_SIZE256 256

volatile LONG charcnt[BUF_SIZE256];

struct tdata {
  DWORD idx;
  char * fileName;
  DWORD tid;
  HANDLE handle;
};

DWORD WINAPI MyThreadFunction(LPVOID param);

int main(int argc, char *argv[]) {
  int pid = _getpid();

  const char *hc_fileName = "../temp/test-w-twice.txt";
  char *fileName;  

  BOOL result;
  DWORD MAX_TIME = 100000;
  int argcmod = argc == 1 ? 1 : argc - 1;

  struct tdata * pthreadData = (struct tdata *) calloc(argcmod,sizeof(struct tdata)); 
  if (pthreadData == NULL)
  {
	  ExitProcess(1);
	}

	HANDLE * phandles = (HANDLE *) calloc(argcmod,sizeof(HANDLE));
  if (phandles == NULL)
  {
  	ExitProcess(1);
  }

  printf("(%d)\th1 START argc:%d\n", pid, argc);
  for (int i = 0; i < argcmod; i++)
  {
  	fileName = (argc == 1) ? hc_fileName : argv[i+1];
  	printf("(%d)\targv[%d]=%s\n", pid, i, fileName); // hc_fileName);// argv[i]);

  	pthreadData[i].idx = i;
  	pthreadData[i].fileName = fileName; 
  	pthreadData[i].handle = CreateThread(NULL, /* LPSECURITY_ATTRIBUTES lpThreadAttributes, */
                                  0, /* SIZE_T dwStackSize, */
                                  MyThreadFunction, /* LPTHREAD_START_ROUTINE lpStartAddress, */
                                  &pthreadData[i], /* LPVOID lpParameter, */
                                  0, /* DWORD dwCreationFlags, */
                                  &pthreadData[i].tid); /* LPDWORD lpThreadId */
  }

  for (int i = 0; i < argcmod; i++) 
    phandles[i] = pthreadData[i].handle;
  
  result = WaitForMultipleObjects(argcmod, phandles, TRUE, MAX_TIME);
  HandleWaitMulResult(result);
  free(phandles);
  free(pthreadData);

  for (int i = 0; i < BUF_SIZE256; ++i)
  	if(charcnt[i] > 0)
  		printf("[%d]\tchar:%c\tcnt:%d\n", i, (char)i, charcnt[i]);

  ExitProcess(0);
}
 

//VOID ThrdFunc(char * fileName)
DWORD WINAPI MyThreadFunction(LPVOID param)
{
	struct tdata *tdata = (struct tdata *) param;
	char * fileName = tdata->fileName;

	char outbuf[BUF_SIZE1]; 
	HANDLE fh = CreateFile(fileName, 
							GENERIC_READ, 
							FILE_SHARE_READ,
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	if(fh == INVALID_HANDLE_VALUE)
	{
		printf("INVALID_HANDLE_VALUE %s\n", fileName);
		return 1; 
	}	

	
	DWORD nRead = 0; 
	int doContinue = 1; 
  BOOL result;

	while(doContinue == 1)
	{
		result = ReadFile(fh, //hFile [in]
			              outbuf, //lpBuffer [out]
			              1, //nNumberOfBytesToRead [in]
			              &nRead,  //lpNumberOfBytesRead [out, optional]
			              NULL//lpOverlapped [in, out, optional])
						  );
		HandleError("ReadFile(fh...)", ! result);

		doContinue = (result != FALSE && nRead == BUF_SIZE1) ? 1 : 0; 
		if (doContinue == 1)
		{
		  	int idx = (int)outbuf[0];
        InterlockedIncrement((LPLONG)&charcnt[idx]);
		}
	}
	result = CloseHandle(fh);
	HandleError("CloseHanlde(fh)", ! result);

	return 0;
}
