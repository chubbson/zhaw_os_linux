/* (C) Hauronen Patronens waste of time projects!
 * https://github.com/chubbson/zhaw_os_linux
 * Author: David Hauri - hauridav
 * Date: 2015-03-29
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
**/

#include <apue.h>
#include <itskylib.h>
#include <field.h>
#include <game.h>
//#include <pthread.h>

hpctf_game * inithpctf__(int mapsize)
{
  hpctf_game * p_hpctf = malloc(sizeof(hpctf_game));
 // fldstruct * fs = initfield_(mapsize);
  p_hpctf->fs = initfield_(mapsize);
  sem_init(&p_hpctf->freeplayerslots, 0, 6); // threadshared, 6 player slots
  p_hpctf->gamestate = WAITING4PLAYERS;

  return p_hpctf;
} 

void inithpctf_(hpctf_game * p_hpctf, int mapsize)
{
  fldstruct * fs = initfield_(mapsize);
/*
  fldstruct * fs = malloc(sizeof(fldstruct));
  initfield(fs, 7);
*/  printfield(fs);

  p_hpctf->fs = fs;

  sem_init(&p_hpctf->freeplayerslots, 0, 6); // threadshared, 6 player slots
  p_hpctf->gamestate = WAITING4PLAYERS;
}

void freehpctf_(hpctf_game * p_hpctf)
{
  freefield_(p_hpctf->fs);
  sem_destroy(&p_hpctf->freeplayerslots);

  free(p_hpctf);

//  freefield(p_hpctf->fs);
//  free(p_hpctf->fs);
}

void inithpctf(hpctf_game *hpctf, int mapsize)
{
	printf("inithpctf a mapsize: '%d'\n", mapsize);

  fldstruct fs; 
  //initfield(&fs, mapsize);
  initfield2(&fs, mapsize);

	printf("fs mapsize: '%d'\n", fs.n);
  

  hpctf->fs = &fs; 

	printf("hpctf fs mapsize: '%d'\n", hpctf->fs->n);
  sem_init(&hpctf->freeplayerslots, 0, 6); // threadshared, 6 player slots

  hpctf->gamestate = WAITING4PLAYERS;

  printfield2(hpctf->fs);

  hpctf->testvar = 95;
}

void freehpctf(hpctf_game *hpctf)
{
  printfield2(hpctf->fs);
  sem_destroy(&hpctf->freeplayerslots);
	printf("%s\n", "a");
////  freefield(hpctf->fs);
//  printfield(hpctf->fs);
  printf("beforefreefield\n");
  printfield2(hpctf->fs);

  freefield2(hpctf->fs);
//  freefield(hpctf->fs);
//  freefield(hpctf->fs);
//#####segdump
	printf("%s\n", "b");
}

void logon(hpctf_game *hpctf)
{
	// decrease the number of free player slots
	// if no slots available, wait for free slots
	sem_wait(&(hpctf->freeplayerslots));
}

void logoff(hpctf_game *hpctf)
{
  // increase the number of free player slots
	sem_post(&(hpctf->freeplayerslots));
}

// some kick but has no player array ...