#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

int main() {
	int chld_fd;
	int prnt_fd;
	pid_t pid;
	char buf[256];

	//make the fifo; a named communications channel
	if (mkfifo("myfifo", 0666) < 0) {
		perror("mkfifo");
		exit(1);
	}

	//fork the process
	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}	

	if (pid ==0) {
	//in the child process
	//want to send message to parent
		//open myfifo and writing
		char str[] = "hello parent!";
		chld_fd = open("myfifo", O_WRONLY);
		write(chld_fd, str, sizeof(str));
		close(chld_fd);
		exit(1);
	}
	else if (pid > 0) {
	//in the parent process
	//open myfifo for reading
		prnt_fd = open("myfifo", O_RDONLY);
		while (read(prnt_fd, &buf, 1) > 0) {
			write(1, &buf, 1);			
		}
		write(1, "\n", 1);
		close(prnt_fd);
		wait(NULL);
		exit(1);	
	}
}
