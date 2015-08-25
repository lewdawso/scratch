#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256

char port[6];
char remote_host[BUF_SIZE];

int  login(void) {
	printf("Enter a remote host to connect to: \n");
	scanf("%s", remote_host);
	printf("Enter the port you want to connect to: \n");
	scanf("%s", port);
	printf("attempting to connect to: %s, %s\n", remote_host, port);
	return (0);
}

int main() {

	int status, socket_d, connect_r;
	struct addrinfo hints, *info, *p;
	char buf[BUF_SIZE];
	char msg[BUF_SIZE] = "what up!\n";

	//let the user login
	login();	
	//set hints addrinfo structure to zero
	memset(&hints, 0, sizeof(hints));

	
	//set some hints; IPv4/IPv6, stream/datagram, passive
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	if ((status = getaddrinfo(remote_host, port, &hints, &info)) < 0) {
		perror("getaddrinfo");
		exit(1);
	}

	//loop through list of addrinfo structures and connect to first one we can
	for (p=info; p != NULL; p = p->ai_next) {
		socket_d = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		//check if return value of socket() is valid descriptor
		if (socket_d < 0) {
			perror("client: socket");
			continue;
		}
		connect_r = connect(socket_d, p->ai_addr, p->ai_addrlen);
		//connect has failed if return value != 0 
		if (connect_r < 0) {
			perror("client: connect");
			continue;
		}
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client failed to connect to server\n");
		exit(1);
	}
	
	//free addrinfo structure info
	freeaddrinfo(info);

	//read messages from the server into a buffer
	if (recv(socket_d, buf, sizeof(buf), 0) < 0) {
		perror("client: recv");
		exit(1);
	}

	//write the contents of the buffer to stout
	printf("Received: %s", buf);

	//send a message to the server
	if (send(socket_d, msg, sizeof(msg), 0) < 0) {
		perror("client: send");
		exit(1);
	}
	
	//close the socket
	close(socket_d);

	return (0);
	
}
