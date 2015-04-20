#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	time_t current_time;
	time(&current_time);

	putenv("TZ=America/Los_Angeles");
	printf("%s", ctime(&current_time));
}