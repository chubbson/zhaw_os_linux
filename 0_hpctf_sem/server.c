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
	printf("USAGE:\n\n%s fieldsizeGreater3\n", argv);
  exit(1);
} 
 
/*
typedef struct {
	int n; // side length
  int** field; // field
  pthread_mutex_t mutfield[4][4];
} fldstruct;

*/
int isfinished(fldstruct *fs)
{
	int n = fs->n;
	int res = fs->field[0][0]; 
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if(res != fs->field[y][x])
				return 0;
		}
	}
	return res;
}

int take(fldstruct *fs, int y, int x, int player)
{
	// todo: mod to phread_mutex_trylock
	// INUSE\n

	// lock field at x y
	pthread_mutex_lock(&fs->mutfield[y][x]);
	fs->field[y][x] = player;
	// send taken to player
	// unlock 
	pthread_mutex_unlock(&fs->mutfield[y][x]);

	int res = isfinished(fs); 
	if(res > 0)
	{
		printf("END %d \n", res);
		return 0;
	} 

	return 1;
}

int main(int argc, char const *argv[])
{
	int n;
	if (argc < 2 || argc != 2 || (n = atoi(argv[1])) < 4)
    usage(argv[0]);

  printf("n: %d\n", n);


  fldstruct fs;
  initfield(&fs, n);

  take(&fs, 1,1, 1);
  printfield(&fs);
  sleep(1);
  take(&fs, 1,2, 2);
  printfield(&fs);
  sleep(1);
  take(&fs, 1,3, 3);
  printfield(&fs);
  sleep(1);
  take(&fs, 2,2, 4);
  printfield(&fs);
  sleep(1);
  take(&fs, 3,2, 5);
  printfield(&fs);
  sleep(1);
  take(&fs, 3,3, 6);

  int res = 0; 
  for(int i = 0; i < n; i++)
  {
  	for(int j = 0; j < n; j++)
 		{
  		res = take(&fs, i,j, 2);
  		if (res == 0)
  			break;
  		printfield(&fs);
  		sleep(1);
  	}
  	if (res == 0)
  		break;
  }

  printfield(&fs);

  freefield(&fs);

  exit(0);
}

