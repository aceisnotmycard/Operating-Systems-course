#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Exec
//Vector
//Path
//Environment
int execvpe(char* program_name, char *argv[], char *envp[]) {
	extern char** environ;
	environ = envp;
	printf("running\n");
	return execvp(program_name, argv);
}

int main(int argc, char** argv) {
	char *envs[] = {
		"NAME1=value1",
		"NAME2=value2",
		(char *) 0
	};
	pid_t cpid;
	if ((cpid = fork()) == 0) {
		// Child process
		execvpe(argv[1], &argv[1], envs);
	} else if (cpid > 0) {
		int status;
		wait(&status);
		printf("Child status is %d\n", WEXITSTATUS(status));
	} else {
		// -1 => error
		perror("fork() failed");
	}
}
