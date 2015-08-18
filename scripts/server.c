#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define PORT "7777" //the port users will be connecting to
#define BACKLOG 20
#define BUF_SIZE 256 

int status, socket_fd, new_fd, bind_r;
struct addrinfo hints, *info, *p;
struct sockaddr_storage conn_addr;
socklen_t addr_size;
char recv_buf[BUF_SIZE];
char *msg = "Message from the server!\n";
char addr[INET_ADDRSTRLEN];

//cast sockaddr to sockaddr_in

void * convert(struct sockaddr * sa) {
	struct sockaddr_in *tmp;
	//do the cast	
	tmp = (struct sockaddr_in *)sa;
	return (&(tmp->sin_addr));
	}

void sig_handler(int signal) {
	if (signal == SIGINT) {
		printf("SIGINT signal received - exiting now\n");
		close(socket_fd);
		exit(1);
	}

}

int main() {
	//set up the signal handler
	signal(SIGINT, sig_handler);

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(NULL, PORT, &hints, &info)) < 0) {
		fprintf(stderr, "failed to get address information");
		exit(1);
	}

	//loop through all results and bind to first we can
	for(p=info; p != NULL; p=p->ai_next) {
		socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if(socket_fd < 0) {
			perror("server: socket");
			continue;
		}
		bind_r = bind(socket_fd, p->ai_addr, p->ai_addrlen);	
		if(bind_r < 0) {
			perror("server: bind");
			continue;
		}
		break;
	} 	

	if (p == NULL) {
		fprintf(stderr, "Failed to bind\n");
		exit(1);
	}

	if (listen(socket_fd, BACKLOG) < 0) {
		perror("listen");
		exit(1);
	}

	printf("Server: waiting for connections\n");

	while(1) {
		addr_size = sizeof(conn_addr);		
		new_fd = accept(socket_fd, (struct sockaddr *)&conn_addr, &addr_size);
		if (new_fd < 1) {
			perror("server: accept");
			continue;
		}
		//print IP of who has connected to the server
		inet_ntop(AF_INET, convert((struct sockaddr *)&conn_addr), addr, sizeof(addr));	
		fprintf(stdout, "Received a connection from: %s\n", addr);
		if (send(new_fd, "test message\n", 13, 0) < 0) {
			perror("send");
		}
		close(new_fd);
	}
	close(socket_fd);
	return (0);
}
