#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
	int sockfd;
	struct addrinfo hints, *res;
	memset(&hints,0, sizeof hints);
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, argv[1], &hints, &res);
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); //HACEMOS EL SOCKET QUE VAMOS A ESCUCHAR

	bind(sockfd, res->ai_addr, res->ai_addrlen);
	listen(sockfd, 20);
	return 0;
}
