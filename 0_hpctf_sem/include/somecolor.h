/* (C) Hauronen Patronens waste of time projects!
* https://github.com/chubbson/zhaw_os_linux
* Author: David Hauri
* Date: 2014-03-15
* License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
*/

#ifndef _LIB_HPWOTP_COLOR
#define _LIB_HPWOTP_COLOR

// \x1B == \033 == \e
#define KNRM  "\x1B[0m"
#define RESET "\033[0m"
#define RESETX "\x1B[0m"
#define RESETE "\e[0m"
#define KBRED  "\x1B[1;31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[0;33m"
#define KBYEL  "\x1B[1;33m"
#define KBLU  "\x1B[34m"
#define KBBLU  "\x1B[1;34m"
#define KMAG  "\x1B[35m"
#define KBMAG  "\x1B[1;35m"
#define KCYN  "\x1B[36m"
#define KBCYN "\x1B[1;36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"
#define KPNK  "\x1B[1;35m"
#define KPRP  "\x1B[0;35m"

#define BLKBLDBLURED "\e[1;5;34;41m"

 /*
const char pink[] = "\e[1;35m";   
const char purple[] = "\e[0;35m"; 
*/
#endif
