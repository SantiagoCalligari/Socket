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
void terminar(int socket);
int queHacer(char *buf);

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
        printf("Login exitoso");
    }
    sistMensaje(new_fd,"quit");    
    close(sockfd);
    shutdown(sockfd,2);
    return 0;
}
