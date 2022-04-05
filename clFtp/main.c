#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int sockfd, rv, numbytes;
    char *puerto, *dominio, buf[512];
    struct addrinfo hints, *servinfo, *p;

    memset(&hints,0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    dominio = argv[1];
    puerto = argv[2];
    rv = getaddrinfo(dominio,puerto, &hints, &servinfo);
    for(p=servinfo; p != NULL; p = p->ai_next)
    {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(connect(sockfd, p->ai_addr, p->ai_addrlen) == -1){
            close(sockfd);
            perror("client:connected");
            continue;
        }
        break;
    }
    if(p==NULL)
    {
            fprintf(stderr,"client failed");
            return 2;
    }
    freeaddrinfo(servinfo);
    if((numbytes = recv(sockfd, buf, sizeof(buf)-1, 0) == -1))
        {
            perror("recv");
            exit(1);
        }
    printf("client '%s'\n",buf);
    close(sockfd);
    return 0;
}
