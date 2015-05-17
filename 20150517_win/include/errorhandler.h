#include <windows.h>

VOID HandleError(LPCTSTR msg, BOOL failure) {
  if (failure) {
    DWORD errorCode =GetLastError();
    LPTSTR errMsg;
    DWORD msgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,  
                                 NULL, 
                                 errorCode, 
                                 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                 (LPTSTR) &errMsg, 
                                 0, 
                                 NULL);
    if (msgLen > 0) {
      printf("%s: errorCode=%ld %s\n", msg, (long) errorCode, errMsg);
    } else {
      printf("%s: errorCode=%ld\n", msg, (long) errorCode);
    }
    if (errMsg != NULL) {
      LocalFree(errMsg);
    }
    ExitProcess(1);
  }
}

VOID HandleWaitMulResult(BOOL result)
{
  printf("threads waited result=%ud ", result);
  switch (result) {
	  case WAIT_ABANDONED:
	    printf("WAIT_ABANDONED");
	    break;
	  case WAIT_OBJECT_0:
	    printf("WAIT_OBJECT_0");
	    break;
	  case WAIT_TIMEOUT:
	    printf("WAIT_TIMEOUT");
	    break;
	  case WAIT_FAILED:
	    printf("WAIT_FAILED");
	    break;
	  default:
	    printf("OTHER");
  }
}