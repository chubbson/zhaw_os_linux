/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri - hauridav
 * Date: 2015-03-29
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

#include <somecolor.h>
#include <field.h>

fldstruct * initfield(int n)
{
	fldstruct * p_fs = malloc(sizeof(fldstruct)); 
	p_fs->n = n;

	p_fs->field = malloc(n * sizeof(square*));
	for (int i = 0; i < n; i++)	
		p_fs->field[i] = malloc(n * sizeof(square));

	for(int y = 0; y < n; y++)
		for (int x = 0; x < n; x++)
			if ((p_fs->field[y][x].value = 0) == 0
				  && pthread_mutex_init(&p_fs->field[y][x].mutex,NULL) != 0) 
		    printf("\n mutex #'%d'|'%d' in mutarr - init failed\n", y, x);

	return p_fs;
}

void freefield(fldstruct *fs)
{
	int n = fs->n;

 	for(int y = 0; y < n; y++)
 	{
 		for(int x = 0; x < n; x++)
 		{
 			if (pthread_mutex_destroy(&fs->field[y][x].mutex) != 0)
	    	printf("\n mutex #'%d'|'%d' in mutarr - clean failed\n", y, x);
	  }
	  free(fs->field[y]);
	}
	free(fs->field);
	free(fs);
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
//			printcolfield(fs->field[y][x]);
			printcolfield(fs->field[y][x].value);// field[y][x]);
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