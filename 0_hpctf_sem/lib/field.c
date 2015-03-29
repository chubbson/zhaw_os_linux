/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri - hauridav
 * Date: 2015-03-29
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

#include <somecolor.h>
#include <field.h>

void initfield(fldstruct *fs, int n)
{
	fs->n = n;
  fs->field = malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
	  fs->field[i] = malloc(n * sizeof(int));
	}

	fs->mutfield = malloc(n * sizeof(pthread_mutex_t*));
	for (int i = 0; i < n; i++) {
	  fs->mutfield[i] = malloc(n * sizeof(pthread_mutex_t));
	}

	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pthread_mutex_init(&fs->mutfield[i][j],NULL) != 0) //lock, NULL)!=0)// (cs->mutarr[i]), NULL) != 0)
		    printf("\n mutex #'%d'|'%d' in mutarr - init failed\n", i, j);
		}
	}
}

void freefield(fldstruct *fs)
{
	int n = fs->n;
	for (int i = 0; i < n; i++) {
	  free(fs->field[i]);
	}
	free(fs->field);

	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pthread_mutex_destroy(&fs->mutfield[i][j]) != 0)
	    	printf("\n mutex #'%d'|'%d' in mutarr - clean failed\n", i, j);
		}
	}

	for (int i = 0; i < n; i++) {
	  free(fs->mutfield[i]);
	}
	free(fs->mutfield);
}

void printcolfield(int i)
{
	if(i < 0)
	{
		printf( KFWHT "%d" RESET, i*i);
		return;
	}

	switch(i%7)
	{
		case 1: 
			printf( KFRED "%d" RESET, i);
			break;
		case 2: 
			printf( KFGRN "%d" RESET, i);
			break;
		case 3:  
			printf( KFYEL "%d" RESET, i);
			break;
		case 4: 
			printf( KFBLU "%d" RESET, i);
			break;
		case 5: 
			printf( KFMAG "%d" RESET, i);
			break;
		case 6: 
			printf( KFCYN "%d" RESET, i);
			break;
		case 0: 
			printf( " " RESET);
			break; 
		default: 
			printf("%d", i);
			break;
	} 
} 

void printfield(fldstruct *fs)
{
	// top border
	for (int i = 0; i < (fs->n+2); ++i)
	{
		printcolfield(-1);
	}
	printf("\n");

	for (int y = 0; y < fs->n; y++)
	{
		// left border
		printcolfield(-1);
		for (int x = 0; x < fs->n; x++)
		{
			printcolfield(fs->field[y][x]);
		}
		// right border 
		printcolfield(-1);
		printf("\n");
	}

	// bottom border
	for (int i = 0; i < (fs->n+2); ++i)
	{
		printcolfield(-1);
	}
	printf("\n");
}