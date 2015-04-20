#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>

#define TABLE_SIZE 101

int main(int argc, char const *argv[]) {
	if (argc == 1) {
		perror("Not enough arguments");
		exit(1);
	}
	const char* filename = argv[1];
	int fd;
	int i, table_length = 1;
	char* table[TABLE_SIZE];
	if ((fd = open(filename, O_RDONLY)) == -1) {
		perror(filename);
		exit(1);
	}

	size_t size = lseek(fd, 0, SEEK_END);
	char* p = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
	table[0] = p;
	for (i = 0; i < size; i++) {
		if (*(p+i) == '\n') {
			table[table_length++] = p+i;
		} else if (i == size - 1) {
			table[table_length++] = p + i + 1;
		}
	}

	struct pollfd fds[1];
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;
	int line_number;
	char* cp;
	while (1) {
		int count = poll(fds, 1, 5 * 1000);
		if (count == -1) {
			perror("poll failed");
			exit(1);
		}
		if (count == 0) {
			printf("No data for reading/writing\n");
		}
		if (fds[0].revents & POLLIN) {
			scanf("%d", &line_number);
			if (line_number < table_length && line_number > 0) {
				// Why -1 in the end? Because there is no '\n' in the end of the last line 
				for (cp = table[line_number-1] + 1; cp <= table[line_number] - 1; cp++) {
					printf("%c", *cp);
				}
				printf("\n");
			} else {
				printf("Maximum possible line is %d\n", table_length - 1);
			}
		} else {
			for (i = 0; i < size; i++) {
				printf("%c", *(p+i));
			}
			break;
		}
	}
	close(fd);
	return 0;
}