//#include <unistd.h>
#include <windows.h>
//#include <stdio.h>

int main(int argc, char const *argv[])
{
	printf("test Hello World\n");
	//scatcolor(4, "whueppa");

	char buf[30];
	int n = 0; 
	buf[0] = '\0';

	n = sprintf(buf, "\x1B[0;37;47m \x1B[0m\n", 0, 7, 7, ' ');

	printf("%s\n", buf);

	getchar();
	exit(0);
}
