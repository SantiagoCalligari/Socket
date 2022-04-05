#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#define BACKLOG 1 //numero de conexiones permitidas al mismo tiempo.

int main(int argc, char *argv[])
{
	//SOCKFD socket escucha, newfd socket conexion, len mensaje
	//their_add direccion de cliente, res resultado deb addrinfo
    int sockfd,  new_fd, len, bytes_sent, rv;  
	char *msg, *puerto;
	struct sockaddr_storage their_addr;
	socklen_t sin_size;
	struct addrinfo hints, *res, *p;
    int yes = 1;
	//hints seteado a 0, puerto igualado a lo enviado en cli
	memset(&hints,0 , sizeof hints);
	puerto = argv[1];
	hints.ai_family = AF_UNSPEC;    //usar ipv4 o ipv6
	hints.ai_socktype = SOCK_STREAM;//tcp
	hints.ai_flags = AI_PASSIVE;	//llenar ip


	if(rv = getaddrinfo(NULL, puerto, &hints, &res)!=0)
    {
        fprintf(stderr, "geatddrinfo: %s \n", gai_strerror(rv));
        return 1;
    }//llena res
	
    for(p=res; p!=NULL; p = p->ai_next)
    {
        if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }
        if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("server: socket");
            continue;
            exit(1);
        }
	    if(bind(sockfd, res->ai_addr, res->ai_addrlen)== -1) // asociamos el puerto con el programa
        {
            close(sockfd);
            perror("server:bind");
            continue;
        }
        break;
    }
    //
    //sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); //HACEMOS EL SOCKET QUE VAMOS A ESCUCHAR
    
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
    freeaddrinfo(res);
    return 0;
}
