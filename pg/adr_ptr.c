#include <stdio.h>

int main(int argc, char const *argv[])
{
  int a, b, *pa, *pb;   /* zwei Variablen und zwei Zeiger deklarieren */
  a = 5; 
  b = 10;

  pa = &a;   /* zeigt nun auf a */
  pb = &b;    /* zeigt nun auf b */

  printf("Zugriff über die Variablen ...\n");
  printf("a = %d, b = %d\n", a, b);   /* altbekannt; einfach den Wert von a und b ausgeben */

  printf("Zugriff durch Dereferenzierung der Zeiger ...\n");
  printf("a = %d, b = %d\n", *pa, *pb);   /* Wichtig: Verweisoperator * nötig! */

  printf("a, b = Variablen mit werten %d %d\n", a, b);
  printf("&a, &b = Adressen der variablen %d %d\n", &a, &b);
  printf("pa=&a, pb=&b = Adressen der variablen %d %d\n", pa, pb);
  printf("*pa, *pb = Wert der in der Adresse liegt %d %d\n", *pa, *pb);
  printf("*&a, *&b = Wert der in der Adresse liegt %d %d\n", *&a, *&b);
  printf("a = %d, b = %d\n", pa, pb);   /* Wichtig: Verweisoperator * nötig! */

  char* c_ptr;
  c_ptr=(char*)malloc(sizeof(char));
  // char* c_ptr: 0x84a5008
  *c_ptr='A';
  // *c_ptr: A
  printf("\n char* c_ptr: %p\n *c_ptr: %c\n and also address char* c_ptr: %d \n",c_ptr,*c_ptr,c_ptr);
  // and also address char* c_ptr: 139087880 

  return 0;
}