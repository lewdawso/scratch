#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>

int main() {

	int status;
	struct addrinfo hints, *info, *p;
	char ipstr [INET6_ADDRSTRLEN];
	char *host = "www.acano.com";
	printf("IPv4 and IPv6 addresses for: %s\n", host);
	

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	status = getaddrinfo(host, "80", &hints, &info);



	for (p = info; p != NULL; p=p->ai_next) {
		void *addr;	
		char *ipver;

		if(p->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;	
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		}
		else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}
		
		//convert network address to printable
		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
		printf("%s: %s\n", ipver, ipstr);
	}
	freeaddrinfo(info);
	return (0);
}
