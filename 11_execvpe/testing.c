#include <stdio.h>

extern char** environ;

int main(int argc, char const *argv[])
{
	char **p;
	printf("hello, i'm child\n");
	for(p = argv; *p != 0; p++) {
		printf("ARG: %s\n", *p);
	}
	for(p = environ; *p != 0; p++) {
		printf("ENV: %s\n", *p);
	}
	return 0;
}