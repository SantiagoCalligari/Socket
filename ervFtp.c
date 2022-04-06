#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#define BACKLOG 1 //numero de conexiones permitidas al mismo tiempo.
#include "comunicar.h"
#include "autenticador.h"
void get(int socket);
void terminar(int socket)
{
    close(socket);
}


int queHacer(char *buf)
{
    int x;
    if(strcmp(buf,"quit") == 0)
        x = 0;
    else if(strcmp(buf,"get") == 0)
            x = 1;
         else
            x = 2;
}
void mainLoop(int socket)
{
    char buf[1024];
    memset(buf,'\0',1024);
    recibir(socket,buf);
    switch(queHacer(buf))
    {
        case 0: terminar(socket);
                     break;
        case 1: get(socket);
                     break;
        case 2: enviarMensaje(socket);
                mainLoop(socket);
                     break;
    }
}

void get(int socket)//aca iria una funcion re copada que mandaria cosas
{
    //algo;
    mainLoop(socket);
} 


int main(int argc, char *argv[])
{
    //SOCKFD socket escucha, newfd socket conexion, len mensaje
    // their_add direccion de cliente, res resultado deb addrinfo
    int sockfd,  new_fd;
    char *puerto=argv[1];
    struct sockaddr_storage their_addr;
    socklen_t sin_size;

    sockfd = socketBindSv(puerto);
   
    sin_size = sizeof their_addr;
    //reconocemos la existencia del cliente.    
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size); 
    if(userLogin(new_fd) == 1)
    {
        mainLoop(new_fd); 
    }
    sistMensaje(new_fd,"quit");    
    close(sockfd);
    shutdown(sockfd,2);
    return 0;
}
