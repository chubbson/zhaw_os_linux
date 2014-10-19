// Realloc sample 
// http://www.tutorialspoint.com/c_standard_library/c_function_realloc.htm

#include <stdio.h>
#include <stdlib.h>

int main()
{
   char *str;
   char *str2;

   str2 = (char *) malloc(15);
   strcpy(str2, "tutorialspoint");
   // = (char *)malloc();

   printf ("sizeof: %d \n", sizeof (*str));

   /* Initial memory allocation */
   str = (char *) malloc(15);
   strcpy(str, "tutorialspoint");
   printf("String = %s,  Address = %u\n", str, str);

   /* Reallocating memory */
   str = (char *) realloc(str, 25);
   strcat(str, ".com");
   printf("String = %s,  Address = %u\n", str, str);

   //free(str);
   
   void *vd; 

   printf ("sizeof: %d \n", sizeof (void));
   printf ("sizeof: %d \n", sizeof (vd));
   printf ("sizeof: %p \n", sizeof (*vd));
   printf ("sizeof: %d \n", sizeof (&vd));

   char **arr = calloc(5, 1*sizeof(char*));
   int i; 
   for (i = 0; i < 5; ++i)
   {
      arr[i] = (char *)calloc(1, 2*sizeof(char));
      if(i%2==0)
      {
         strcat(arr[i],"aac");
      }
      else
      {
         strcat(arr[i],"ab");
         //arr[i] = str2;
      }
   }


   for (i = 0; i < 5; ++i)
   {
      printf("String = %s,  Address = %u\n", arr[i], arr[i]);  /* code */
   }
   /*
   printf("String = %s,  Address = %u\n", arr[0], arr[0]);
   printf("String = %s,  Address = %u\n", arr[1], arr[1]);
   */

   if(str != NULL)
   {
      printf("str is not null \n");
   }


   free(str);
   if(str != NULL)
   {
      printf("str is not null \n");
   }
   free(arr);


   return(0);
}