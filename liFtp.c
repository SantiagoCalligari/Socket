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
    memset(buf,'\0',1024);
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


int main(int argc, char *argv[])
{
    int numbytes, sockfd;
    char *puerto, *dominio, buf[1024];
    
    dominio = argv[1];
    puerto = argv[2];
    sockfd = conectar(puerto,dominio);
    if(sockfd == -1)
        return -1;
    mainLoop(sockfd);
    close(sockfd);
    return 0;
}
