#include <stdio.h>
#include <unistd.h>

void task(const char* filename) {
	FILE* file;

	printf("user id = %d \n", getuid());
	printf("effective user id = %d\n", geteuid());

	file = fopen(filename, "r");
	if (NULL != file) {
		fclose(file);
	} else {
		perror("Can't open file");
	}
}

int main(int argc, char const *argv[]){
	task(argv[1]);
	if (-1 == setuid(getuid())) {
		perror("Can't set effective uid to real id");
		return 1;
	}
	task(argv[1]);	
}
