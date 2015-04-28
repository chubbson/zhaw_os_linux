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
#include "include/errorhandler.h"

int main(int argc, char *argv[]) {
  BOOL result;
  
  printf("in child process\n");
  Sleep(10000);
  printf("done in child process\n");
  ExitProcess(0);
}

