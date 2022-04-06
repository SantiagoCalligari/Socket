#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include "comunicar.h"

void mainLoop(int socket)
{
    int continuar = 1;
    char buf[1024];
    while(continuar)
    {
        recibir(socket,buf);
        printf("%s", buf);
        if(strcmp(buf,"quit") == 0)
            break;
        memset(buf,0,1024);
        enviarMensaje(socket);

    }
}

int conectar(char *puerto, char *dominio)
{
    int sock,rv;
    struct addrinfo hints, *res, *p;
    
    memset(&hints,0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    rv = getaddrinfo(dominio,puerto, &hints, &res);
    for(p=res; p != NULL; p = p->ai_next)
    {
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(connect(sock, p->ai_addr, p->ai_addrlen) == -1){
            close(sock);
            perror("client:connected");
            continue;
        }
        break;
    }
    if(p==NULL)
    {
        return -1;
    }

    freeaddrinfo(res);
    return sock;
}

int main(int argc, char *argv[])
{
    int numbytes, sockfd;
    char *puerto, *dominio, buf[1024];
    
    dominio = argv[1];
    puerto = argv[2];
    sockfd = conectar(puerto,dominio);
    
    mainLoop(sockfd);
    close(sockfd);
    return 0;
}
