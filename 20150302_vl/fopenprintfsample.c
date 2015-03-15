#include <stdio.h>
#define FILENAME "test.txt"

int main(void)
{
    FILE *myfile;
    char string[81] = {'\0'};

    myfile=fopen(FILENAME , "r");
    if(myfile == NULL)
    {
        printf("The file test.txt could not be found! Exiting...\n");
        return -1;
    }
    while(fscanf(myfile, " %80[^\n]s", string) != EOF)
    {
        printf("%s\n", string);
    }
    fclose(myfile);


    printf("%s\n", "after close before exit");

    return 0;
}