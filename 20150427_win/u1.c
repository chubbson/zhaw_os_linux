/*
ANALOG /DEV/TTY gibt es hier CONIN$ CONOUT$
nicht immer ist console überhaupt vorhanden
ausgabe mit WriteFile || WriteConsole
Eingabe mit ReadFile || ReadConsole
*/

#include <windows.h>
//#include <stdio.h>

#define BUF_SIZE (61)

int main(int argc, char const *argv[])
{
	char inBuffer[BUF_SIZE];
  DWORD nBytesToRead      = BUF_SIZE;
  DWORD dwBytesRead       = 0;
  OVERLAPPED stOverlapped = {0};

  BOOL bResult   = FALSE;
  BOOL bContinue = TRUE;

	//while(bContinue)
	//{
	  // Default to ending the loop.
	  bContinue = FALSE;
	       
	  // Attempt an asynchronous read operation.
	  bResult = CreateFile(CONIN$, //hFile,
	  	 									 GENERIC_READ,
	  	 									 FILE_SHARE_READ,
	  	 									 FALSE, 
	  	 									 OPEN_EXISTING, 
	  	 									 NULL,
	  	 									 NULL);

	  /*new*/

	  HANDLE fh1; 
	  DWORD nWritten; 

	  fh1 = CreateFile("CONOUT$",
	  	               GENERIC_WRITE,
	  	               0,
	  	               NULL,
	  	               CREATE_ALWAYS,
	  	               FILE_ATTRIBUTE_NORMAL,NULL);

	  result = WriteFile(fh1,);

/*
	                     inBuffer,
	                     nBytesToRead,
	                     &dwBytesRead,
	                     &stOverlapped);

	  dwError = GetLastError();

    // Check for a problem or pending operation. 
    if (!bResult) 
    {
    	printf("%s\n", "Error?"); 
    }
    else
    {
    	printf("ReadFile completed synchronously\n");
    }
	}

	printf("what we read: %s\n", inb);
	*/
	getchar();
	exit(0);
}
