#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>

static int sockfd;
static struct addrinfo hints, *res; 

const char *addr = "www.google.co.uk";
const char *port = "443";

int main (int argc, char *argv[]) {

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((getaddrinfo(addr, port, &hints, &res)) != 0) {
        perror("getaddrinfo");
        return 1;
    }
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
        perror("socket");
        return 1;
    }
    
    if ((connect(sockfd, res->ai_addr, res->ai_addrlen)) == -1) {
        perror("connect hmm");
        return 1;
    }

    return 0;
}
