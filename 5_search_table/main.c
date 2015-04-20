#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFER_SIZE 1

int main(int argc, char const *argv[])
{
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

	//printf("%d\n", fd);
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
	printf("\n-1%d lines\n", i);

	int line_number;
	char* str;
	while (1) {
		printf("\nEnter -1 to exit\n");
		printf("Enter line number: ");
		scanf("%d", &line_number);

		if (-1 == line_number) {
			break;
		}


		if (line_number > i - 1) {
			printf("Sorry text has no %dth line. \n", line_number);	
		} else {
			int len = table[line_number] - table[line_number - 1] + 1;
			str = (char*) malloc(sizeof(char) * len);
			lseek(fd, table[line_number - 1], SEEK_SET);
			read(fd, str, len);
			str[len - 1] = '\0';
			printf("%d: %s", line_number, str);
			free(str);
		}
	}

	lseek(fd, 0, SEEK_SET);
	if (0 != close(fd)) {
		perror("Cannot close file");
	}
}
