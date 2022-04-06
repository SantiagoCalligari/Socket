#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#define BACKLOG 1 //numero de conexiones permitidas al mismo tiempo.


int socketbind(char *puerto)
{
    struct addrinfo hints, *res, *p;
    int sock, rv;
    int yes = 1;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;    //usar ipv4 o ipv6
    hints.ai_socktype = SOCK_STREAM;//tcp
    hints.ai_flags = AI_PASSIVE;	//llenar ip

    if(rv = getaddrinfo(NULL, puerto, &hints, &res)!=0)
        return -1;
    
    for(p=res;p!=NULL;p = p->ai_next)
    {
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if(bind(sock,res->ai_addr, res->ai_addrlen) == -1)
            close(sock);
        break;
    }
    freeaddrinfo(res);
        
    return sock;
}

int main(int argc, char *argv[])
{
//SOCKFD socket escucha, newfd socket conexion, len mensaje
// their_add direccion de cliente, res resultado deb addrinfo
    int sockfd,  new_fd, len, bytes_sent;  
    char *msg, *puerto;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    //hints seteado a 0, puerto igualado a lo enviado en cli
    puerto = argv[1];


    sockfd = socketbind(puerto);
   
    listen(sockfd, BACKLOG); // escuchamos al puerto que asociamos
    printf("Buscando conexiones\n");
//	while(1)
    {
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size); //reconocemos la existencia del cliente.
    
        printf("supuestamente aceptamos desde\n");	
        if(!fork())
        {
            close(sockfd);
            if(send(new_fd, "Hello, World", 13, 0) == -1)
                perror("send");
            close(new_fd);
            exit(0);
        }
        close(new_fd);
    }

    //shutdown(sockfd,2);
    //shutdown(new_fd,2);
    return 0;
}
