cl h8.c

H8 (2015-05-04)
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
cl h8.c
counting chars with seperate threads per given file argument using interlock

h8.exe | starts 1 thread reading fallback hardcoded file, ../temp/test-w-twice.txt
h8.exe asdf | if asdf does not exist, file open failes but programm dint crash
h8.exe h8.c | counts each character of h8.c if it does exist
h8.exe h8.c README.md | if both files exist, count all charactes 
h8.exe h8.c READMI.md h8.exe ...| and so on, prog does not stop if one file in arg couldnt opened.  


