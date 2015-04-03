/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri - hauridav
 * Date: 2015-03-29
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

#include <somecolor.h>
#include <field.h>


int initfield2(fldstruct *fs, int n)
{
	fs->n = n;

	fs->field2_tmp = (struct fld *)malloc(sizeof(fld)*n*n);
	if(fs->field2_tmp == NULL)
		return EXIT_FAILURE;
	fs->field2 =  (struct fld **) malloc(sizeof(struct fld *)*n);
	if(fs->field2 == NULL)
		return EXIT_FAILURE;

	for(int i = 0; i < n; i++)
		fs->field2[i] = fs->field2_tmp + i * n;

	for(int y = 0; y < n; y++)
		for(int x = 0; x < n; x++)
		{
			if (pthread_mutex_init(&(fs->field2[y][x].mutex),0) != 0)
		    printf("\n mutex #'%d'|'%d' in mutarr - init failed\n", y, x);
		  fs->field2[y][x].value = 0;
		}
}

void freefield2(fldstruct *fs)
{
	int n = fs->n;
	free(fs->field2);
	free(fs->field2_tmp);
}

fldstruct * initfield_(int n)
{
	fldstruct * p_fs = malloc(sizeof(fldstruct)); 
	p_fs->n = n;
  p_fs->field = malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
	  p_fs->field[i] = malloc(n * sizeof(int));
	}

	p_fs->mutfield = malloc(n * sizeof(pthread_mutex_t*));
	for (int i = 0; i < n; i++) {
	  p_fs->mutfield[i] = malloc(n * sizeof(pthread_mutex_t));
	}

	for(int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if (pthread_mutex_init(&p_fs->mutfield[y][x],NULL) != 0) //lock, NULL)!=0)// (cs->mutarr[i]), NULL) != 0)
		    printf("\n mutex #'%d'|'%d' in mutarr - init failed\n", y, x);
		}
	}

	return p_fs;
}

void freefield_(fldstruct *fs)
{
	int n = fs->n;
	for (int i = 0; i < n; i++) {
	  free(fs->field[i]);
	}
	free(fs->field);

	for(int y = 0; y < n; y++)
	{
		for (int x = 0; x < n; x++)
		{
			if (pthread_mutex_destroy(&fs->mutfield[y][x]) != 0)
	    	printf("\n mutex #'%d'|'%d' in mutarr - clean failed\n", y, x);
		}
	}

	for (int i = 0; i < n; i++) {
	  free(fs->mutfield[i]);
	}
	free(fs->mutfield);
	free(fs);
}

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
			printf("init %d %d\n",i,j );
			if (pthread_mutex_init(&fs->mutfield[i][j],NULL) != 0) //lock, NULL)!=0)// (cs->mutarr[i]), NULL) != 0)
		    printf("\n mutex #'%d'|'%d' in mutarr - init failed\n", i, j);
		}
	}
}

void freefield(fldstruct *fs)
{
	printf("freefield start\n");
	//printf("1 n: %n\n", fs->n);
	int n = fs->n;

	printf("freefield start\n");

	for (int i = 0; i < n; i++) {
		printf("fs->field[%d]\n",i);
	  free(fs->field[i]);
	}
	free(fs->field);

	printf("1 n: %d\n", fs->n);

	printf("2\n");

	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d %d\n",i,j );

			// segmentation fault core dump ....
			if (pthread_mutex_destroy(&fs->mutfield[i][j]) != 0)
	    	printf("\n mutex #'%d'|'%d' in mutarr - clean failed\n", i, j);
		}
	}

	printf("3\n");

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

void printfield2(fldstruct *fs)
{
	// top border
	printf("printfield 2n: %d\n", fs->n);
	return;

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
			printcolfield(fs->field2[y][x].value);
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