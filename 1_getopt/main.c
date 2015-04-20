#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ulimit.h>

extern char **environ;

void printRealAndEffectiveId();
void makeMeLeader();
void printProcessId();
void printUlimit();
void setUlimit(char *new_value);
void printCurrentDirectory();
void printEviron();
void setEnviron(char* param);
void printCore();
void setCore(char* new_value);

int main(int argc, char *argv[], char* envp[]) {

	char options[] = "pisuU:dvV:cC:";
	int c, dflg = 0, fflg = 0, gflg = 0;
	char *f_ptr, *g_ptr;

	while ((c = getopt(argc, argv, options)) != EOF) {
		switch (c) { 
			case 'i':
				printRealAndEffectiveId();
				break; 
			case 's':
				makeMeLeader();
				break;
			case 'p': 
				printProcessId();
				break; 
			case 'u':
				printUlimit();
				break;
			case 'U':
				setUlimit(optarg);
				break;
			case 'd':
				printCurrentDirectory();
				break;
			case 'v':
				printEviron();
				break;
			case 'V':
				setEnviron(optarg);
				break;
			case 'c':
				printCore();
				break;
			case 'C':
				setCore(optarg);
				break;
			case '?':
				printf("invalid option is %c\n", optopt);
		}
	}
}

void printRealAndEffectiveId() {
	printf("user id = %d \n", getuid());
	printf("effective user id = %d\n", geteuid());
	printf("group id = %d \n", getpid());
	printf("effective group id = %d\n", getegid());
}

void makeMeLeader() {
	if (0 > setpgid(0, 0)) {
		perror("Cannot set current process as leader");
	} else {
		printf("This process is now leader of the group\n");
	}
}

void printProcessId() {
	printf("Process ID: %d\n", getpid());
	printf("Parent ID: %d\n", getppid());
	printf("Group ID: %d\n", getpgid(0));
}

void printUlimit() {
	struct rlimit strct;
	getrlimit(RLIMIT_NPROC, &strct);
	printf("ulimit: %llu\n", strct.rlim_cur);
}

void setUlimit(char* new_value) {
	long limit = atol(new_value);
	struct rlimit strct;
	getrlimit(RLIMIT_NPROC, &strct);
	if (limit > strct.rlim_max) {
		printf("Maximum possible value is %llu\n", strct.rlim_max);
		return;
	}

	strct.rlim_cur = limit;	

	if (0 > setrlimit(RLIMIT_NPROC, &strct)) {
		perror("Cannot set new limit");
		return;
	} else {
		printf("Success! New ulimit is %llu\n", strct.rlim_cur);
	}
}

void printCurrentDirectory() {
	char buf[1000];
	printf("Current directory is %s\n", getcwd(buf, 1000));
}

void printEviron() {
	char **p;
	for (p = environ; *p; p++)
        printf("%s\n", *p);
}

void setEnviron(char* param) {
	if (0 > putenv(param)) {
		perror("Cannot set or add env variable");
	}
}

void printCore() {
	struct rlimit strct;
	getrlimit(RLIMIT_CORE, &strct);
	printf("Maximum core file size: %llu\n", strct.rlim_cur);
}

void setCore(char* new_value) {
	long limit = atol(new_value);
	struct rlimit strct;
	getrlimit(RLIMIT_CORE, &strct);
	if (limit > strct.rlim_max) {
		printf("Maximum possible value is %llu\n", strct.rlim_max);
		return;
	}
	if (limit < strct.rlim_cur) {
		printf("Minimum possible value is %llu\n", strct.rlim_cur);
		return;
	}
	strct.rlim_cur = limit;
	if (0 > setrlimit(RLIMIT_CORE, &strct)) {
		perror("Cannot set new core file size limit");
		return;
	} else {
		printf("Success! new core file size limit is %llu\n", strct.rlim_cur);
	}
}
