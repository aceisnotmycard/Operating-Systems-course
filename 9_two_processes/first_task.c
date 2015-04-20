#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	const char* filename = argv[1]; 
	pid_t cpid;
	if ((cpid = fork()) == 0) {
		// Child process
		execl("/bin/cat", "cat", argv[1], (char *) 0);
	} else if (cpid > 0) {
		// Parent
		printf("Hello, this is %d's dad\n", cpid);
	} else {
		// -1 => error
		perror("fork() failed");
	}
	exit(0);
}
