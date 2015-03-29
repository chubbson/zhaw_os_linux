/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri - hauridav
 * Date: 2015-03-29
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

#include <apue.h>
#include <itskylib.h>
#include <field.h>

void usage(const char *argv)
{
	printf("USAGE:\n\n%s fieldsize\n", argv);
  exit(1);
} 
 
/*
typedef struct {
	int n; // side length
  int** field; // field
  pthread_mutex_t mutfield[4][4];
} fldstruct;

*/


int take(fldstruct *fs, int y, int x, int player)
{
	// lock field at x y
	pthread_mutex_lock(&fs->mutfield[y][x]);
	fs->field[y][x] = player;
	// send taken to player
	// unlock 
	pthread_mutex_unlock(&fs->mutfield[y][x]);
	return 0;
}

int main(int argc, char const *argv[])
{
	if (argc < 2 || argc != 2)
    usage(argv[0]);

  int n = atoi(argv[1]);

  fldstruct fs;
  initfield(&fs, n);

  take(&fs, 1,1, 1);
  take(&fs, 1,2, 2);
  take(&fs, 1,3, 3);
  take(&fs, 2,2, 4);
  take(&fs, 3,2, 5);
  take(&fs, 3,3, 6);

  printf("n: %d\n", n);
  printfield(&fs);

  freefield(&fs);

  exit(0);
}

