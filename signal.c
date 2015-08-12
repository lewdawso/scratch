#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sig_handler(int signal) {
	if (signal == SIGINT) {
		printf("SIGINT signal received\n");
		exit(1);
	}
	else if (signal == SIGSEGV) {
		printf("SIGSEGV signal received\n");
		exit(1);
	}
}

void main() {
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	//induce a SIGSEGV by dereferencing a dodgy pointer
	int *p=0;
	int i = *p;
}
