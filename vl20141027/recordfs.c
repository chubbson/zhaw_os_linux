/**
 * Author: David Hauri 
 * Thema: polimorph sample in c
 * gcc Sample: gcc polimorphical-hw.c -o polimorphical-hw -lm
 * HINT: DONT Miss the -lm directive!!
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


struct rec {
	char name[256];
	int kontoNr;
	double groesse; 
};

void rec_print(struct rec *r){
	printf("Recordname: %s: kontNr: %d groesse: %f\n", r->name, r->kontoNr, r->groesse);
}

int main(int argc, char const *argv[])
{
	// seed random sequence
	srand(time(NULL));

	int RECCNT = 10;

  	struct rec *recs;
  	struct rec *recsread;
  	// allocate memory for an aray of records
  	  // allocate memorey for pthread_creat() arguments
    recs = calloc(10, sizeof(struct rec));

	FILE *fp;
	char str[] = "This is tutorialspoint.com";

	// write files; 
	fp = fopen( "file.txt" , "w" );
	fseek(fp, SEEK_SET, 0);

	int i = 0; 
	for(i = 0; i < RECCNT; i++)
	{
			recs[i].kontoNr = rand()%15;
			recs[i].groesse = ((double)rand()/(double)RAND_MAX);// rand()%15d;
			rec_print(&recs[i]);


	}
		fwrite(recs , sizeof(struct rec) , 10 , fp );

	fclose(fp);
	free(recs);


  	//struct rec *recsread;
    recsread = calloc(10, sizeof(struct rec));
	fp = fopen("file.txt","r");
	fseek(fp, SEEK_SET, 0);
	// read all
	fread(recsread, sizeof(struct rec), 10, fp);
	// read file: 
  	for(i = 0; i < RECCNT; i++)
	{
		// read element first element -.-
		//fread(recsread, sizeof(struct rec), 1, fp);
		rec_print(&recsread[i]);
	}
	fclose(fp);

	free(recsread);

	/* code */
	return 0;
}