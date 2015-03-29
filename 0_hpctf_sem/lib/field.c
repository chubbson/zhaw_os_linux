#include <somecolor.h>
#include <field.h>

void initfield(fldstruct *fs, int n)
{
	fs->n = n;
  fs->field = malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
	  fs->field[i] = malloc(n * sizeof(int));
	}
}

void freefield(fldstruct *fs)
{
	int n = fs->n;
	for (int i = 0; i < n; i++) {
	  free(fs->field[i]);
	}
	free(fs->field);
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