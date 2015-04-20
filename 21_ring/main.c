#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define   RING   '\07'

int count;
//comment
void sigcatch(int sig);

int main()
{
	signal(SIGINT, sigcatch);
	while(1)
	 	pause();
}

void sigcatch(int sig) {
	if (sig == SIGQUIT) {
		printf("Number of rings: %d\n", count);
		exit(1);
	}
	printf("%c\n", RING);
	count++;
	signal(sig, sigcatch);
}
