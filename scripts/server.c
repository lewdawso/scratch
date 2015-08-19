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
#include <sys/select.h>

#define PORT "7777" //the port users will be connecting to
#define BACKLOG 20 //how many concurrent connections we allow
#define BUF_SIZE 256 //read or write buffer size

//cast sockaddr to sockaddr_in

void * convert(struct sockaddr * sa) {
	struct sockaddr_in *tmp;
	//do the cast	
	tmp = (struct sockaddr_in *)sa;
	return (&(tmp->sin_addr));
}

//print out IP address of new connection
void print_connection(struct sockaddr_storage conn_addr, char *addr) {
	inet_ntop(AF_INET, convert((struct sockaddr *)&conn_addr), addr, sizeof(addr));	
	fprintf(stdout, "received a connection from: %s\n", addr);
}

//create new socket when we have a connection
int new(int socket_fd, struct sockaddr_storage conn_addr, socklen_t addr_size) {
	int des;
	des = accept(socket_fd, (struct sockaddr *)(&conn_addr), &addr_size);
	return des;
}

//signal handler
void sig_handler(int signal) {
  if (signal == SIGINT) {
  printf("SIGINT signal received - exiting now\n");
  exit(1);
  }
 }

//function to make sure we send everything that's in our buffer
int sendall(int s, char *buf, int len) {
	int char_sent = 0;	
	int char_left = len;

	while (char_left) {
	char_sent = send(s, buf + char_sent, char_left, 0);
	char_left -= char_sent;
	}
	return (char_left = 0 ? 0:-1);
	
}

int main() {

	int socket_fd, new_fd, max_fd, bytes, i;
	struct addrinfo hints, *info, *p;
	struct sockaddr_storage conn_addr;
	socklen_t addr_size;
	char recv_buf[BUF_SIZE];
	char msg[BUF_SIZE] = "message from the server!\n";
	char addr[INET_ADDRSTRLEN];

	//variables required for selec() i.e. monitoring of sets of multiple file descriptors
	struct fd_set readfds, core;
	FD_ZERO(&core);
	FD_ZERO(&readfds);
	
	//set up the signal handler
	signal(SIGINT, sig_handler);

	//create a socket and bind to it
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, PORT, &hints, &info) < 0) {
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
		if ( bind(socket_fd, p->ai_addr, p->ai_addrlen) < 0) {	
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

	//add listener socker to core
	FD_SET(socket_fd, &core);

	//max_fd is the listener socket at this point
	max_fd = socket_fd;

	printf("*** WAITING FOR CONNECTIONS ***\n");

	//main loop
	for(;;) {
		//check for an error in select
		//readfds is modified by select() to show only those that are "ready" for an operation
		//so replace is each time with the core list of fd's to reset the states
		readfds = core;
		if(select(max_fd + 1, &readfds, NULL, NULL, NULL) == -1) {
			perror("select");
			exit(1);
		}
		//need to check if there are any updates to our file descriptors
		for(i=0; i<=max_fd; i++) {
			if(FD_ISSET(i, &readfds)) {
				if(i == socket_fd) {
					//new connection
					new_fd = new(socket_fd, conn_addr, addr_size);
					if(new_fd < 0) {
						perror("accept");
					} else {
						//add new_fd to set
						FD_SET(new_fd, &core);
						//increment max fd's
						if(new_fd > max_fd) {
							max_fd = new_fd;
						}
						print_connection(conn_addr, addr);
						sendall(new_fd, msg, sizeof(msg));								}

				} else {
					//received data from a client that's already connected
					if((bytes = recv(i, recv_buf, sizeof(recv_buf), 0)) <= 0) {
						if(bytes == 0) {
							printf("socket %d hung up\n", i);
						} else {
							perror("server: recv");
						}
						close(i);
						FD_CLR(i, &core);
					} else {	
						//print data to stdout
						printf("message received from the client: %s", recv_buf);

					}
				}
			}
		}
	}
}
