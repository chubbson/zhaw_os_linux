/* (C) Hauronen Patronens waste of time projects!
* https://github.com/chubbson/zhaw_os_linux
* Author: David Hauri
* Date: 2014-03-16
* License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
*/

#ifndef _LIB_HPWOTP_COPROCPIPES
#define _LIB_HPWOTP_COPROCPIPES

#define NUM_PIPES          2
 
#define PARENT_WRITE_PIPE  0
#define PARENT_READ_PIPE   1

int pipes[NUM_PIPES][2];

/* always in a pipe[], pipe[0] is for read and
   pipe[1] is for write */
#define FD_READ  0
#define FD_WRITE 1
 
#define FD_PARENT_READ  /*(pipes[0])[0] = fd1[0]*/( pipes[PARENT_READ_PIPE][FD_READ]   ) 
#define FD_PARENT_WRITE /*(pipes[1])[1] = fd2[1]*/( pipes[PARENT_WRITE_PIPE][FD_WRITE] )
 
#define FD_CHILD_READ   /*(pipes[1])[0] = fd2[0]*/( pipes[PARENT_WRITE_PIPE][FD_READ]  )
#define FD_CHILD_WRITE  /*(pipes[0])[1] = fd1[1]*/( pipes[PARENT_READ_PIPE][FD_WRITE]  )

#endif