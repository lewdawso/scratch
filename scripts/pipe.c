#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

int main() {
	pid_t pid;
	int pipefd[2];
	char buf[256];

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(1);
	}

	//for the process
	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}	

	if (pid ==0) {
	//child process
		close(pipefd[1]);
		while(read(pipefd[0], &buf, 1) > 0) {
			//write from buffer to stdout
			write(1, &buf, 1);
		}
	write(1, "\n", 1);
	close(pipefd[0]);
	_exit(1);
	}
	
	else if (pid > 0) {
	//parent process
	close(pipefd[0]);
	write(pipefd[1], "test", 4);
	close(pipefd[1]);
	wait(NULL);
	exit(1);	
	}
}
