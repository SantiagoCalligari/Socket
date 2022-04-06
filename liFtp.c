#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include "comunicar.h"

int loginCl(int socket,char *buf)
{
    char userRta[] = "USER ",tmp[128], passRta[] = "PASS";
    memset(buf,'\0',1024);
    recibir(socket,buf);
    printf("%s",buf);

    scanf("%[^\n]",tmp);
    getchar();
    strcat(userRta,tmp);
    sistMensaje(socket, userRta);

    memset(buf,'\0',1024);
    recibir(socket,buf);
    printf("%s",buf);

    scanf("%[^\n]",tmp);
    getchar();
    strcat(passRta,tmp);
    sistMensaje(socket, passRta);

    
    printf("finalStr, %s",passRta);
}
void mainLoop(int socket)
{
    
}


int main(int argc, char *argv[])
{
    int numbytes, sockfd;
    char buf[1024];
    
    sockfd = conectar(argv[2], argv[1]);
    if(sockfd == -1)
        return -1;
    
    loginCl(sockfd, buf);
    close(sockfd);
    return 0;
}
