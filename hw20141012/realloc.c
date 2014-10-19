// Realloc sample 
// http://www.tutorialspoint.com/c_standard_library/c_function_realloc.htm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   char *str;
   printf ("sizeof: %d \n", sizeof (*str));

   /* Initial memory allocation */
   str = (char *) malloc(15);
   strcpy(str, "tutorialspoint");
   printf("String = %s,  Address = %u\n", str, *str);

   /* Reallocating memory */
   str = (char *) realloc(str, 25);
   strcat(str, ".com");
   printf("String = %s,  Address = %u\n", str, *str);

   return(0);
}