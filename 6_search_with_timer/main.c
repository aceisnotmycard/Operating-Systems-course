#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <unistd.h>
#include <time.h>
#include <poll.h>

#define BUFFER_SIZE 1


void print_line(int line, int size, int* table, int fd) {
	if (line > size - 1) {
		printf("Sorry text has no %dth line. \n", line);	
	} else {
		int len = table[line] - table[line - 1] + 1;
		char* str = (char*) malloc(sizeof(char) * len);
		lseek(fd, table[line - 1], SEEK_SET);
		read(fd, str, len);
		str[len - 1] = '\0';
		printf("%d: %s", line, str);
		free(str);
	}
}

int main(int argc, char const *argv[])
{
	time_t time_end, time_start;
	int end_pos, cur_pos;
	int i, k;
	int table[100];
	for (i = 0; i < 100; i++) {
		table[i] = 0;
	}

	int fd = open(argv[1], O_RDONLY);
	if (-1 == fd) {
		perror("Cannot open file");
		return 0;
	}

	char buf[BUFFER_SIZE];
	i = 1;

	end_pos = lseek(fd, 0, SEEK_END);
	cur_pos = lseek(fd, 0, SEEK_SET);
	while (cur_pos != end_pos) {
		read(fd, buf, 1);
		printf("%c", buf[0]);
		if ('\n' == buf[0]) {
			table[i] = lseek(fd, 0, SEEK_CUR);
			i++;
		}
		cur_pos++;
	}
	int number_of_strings = i;

	int line_number;
	int is_read = 0;

    struct pollfd fds[1];
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;

	while (1) {
		is_read = 0;
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
			is_read = 1;
		}
		if (!is_read) {
			int j;
			for(j = 1; j < number_of_strings; j++) {
				print_line(j, number_of_strings, table, fd);
			}
			break;
		} else {
			if (-1 == line_number) {
				break;
			}
			print_line(line_number, number_of_strings, table, fd);
		}
	}

	lseek(fd, 0, SEEK_SET);
	if (0 != close(fd)) {
		perror("Cannot close file");
	}
}