#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	const char* filename = argv[1]; 
	pid_t cpid;
	if ((cpid = fork()) == 0) {
		// Child process
		execv(argv[1], &argv[1]);
		exit(1);
	} else if (cpid > 0) {
		int status;
		wait(&status);
		printf("Child status is %d\n", WEXITSTATUS(status));
	} else {
		// -1 => error
		perror("fork() failed");
	}
	exit(0);
}