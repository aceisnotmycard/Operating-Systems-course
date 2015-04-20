#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char const *argv[]) {
	struct flock lock;
	int fd;

	if (-1 == (fd = open(argv[1], O_RDWR))) {
		perror(argv[1]);
		exit(1);
	}

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	if (-1 == fcntl(fd, F_SETLK, &lock)) {
		if (EACCES == errno || EAGAIN == errno) {
			printf("%s is locked.", argv[1]);
			exit(1);
		}
	}

	int vim_length = strlen("vim");
	int arg_lenth = strlen(argv[1]);
	char* command = malloc(sizeof(char) * (arg_lenth + vim_length + 2));
	snprintf(command, arg_lenth + vim_length + 2, "vim %s", argv[1]);
	system(command);

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	close(fd);
	return 0;
}