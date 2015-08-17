#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>

#define PORT "7777"
#define BACKLOG 20

int main() {

	int status, socket_fd, new_fd;
	struct addrinfo hints, *info;
	struct sockaddr *conn_addr;
	socklen_t addr_size;
	

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	status = getaddrinfo(NULL, PORT, &hints, &info);

	
	//make a socket
	socket_fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);

	//bind it to port on local machine
	bind(socket_fd, info->ai_addr, info->ai_addrlen);

	//listen
	listen(socket_fd, BACKLOG);

	//accept incoming connections on sockets
	addr_size = sizeof(*conn_addr);
	new_fd = accept(socket_fd, conn_addr, &addr_size);

	return (0);
}
