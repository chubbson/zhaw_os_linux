/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri
 * Date: 2015-03010
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

 #ifndef _LIB_HPWOTP_TELLWAIT
#define _LIB_HPWOTP_TELLWAIT

#include "apue.h"

static void
sig_usr(int signo);

void TELL_WAIT(void);
void TELL_PARENT(pid_t pid);
void WAIT_PARENT(void);
void TELL_CHILD(pid_t pid);
void WAIT_CHILD(void);

#endif