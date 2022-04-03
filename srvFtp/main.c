#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>

#define BACKLOG 1 //numero de conexiones permitidas al mismo tiempo.

int main(int argc, char *argv[])
{

	//SOCKFD socket escucha, newfd socket conexion, len mensaje
	//their_add direccion de cliente, res resultado de addrinfo
	int sockfd, new_fd, len, bytes_sent;  
	char *puerto, *msg;
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	struct addrinfo hints, *res;


	//hints seteado a 0, puerto igualado a lo enviado en cli
	memset(&hints,0, sizeof hints);
	puerto = argv[1];

	hints.ai_family = AF_UNSPEC;    //usar ipv4 o ipv6
	hints.ai_socktype = SOCK_STREAM;//tcp
	hints.ai_flags = AI_PASSIVE;	//llenar ip


	getaddrinfo(NULL, puerto, &hints, &res);//llena res
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); //HACEMOS EL SOCKET QUE VAMOS A ESCUCHAR

	bind(sockfd, res->ai_addr, res->ai_addrlen); // asociamos el puerto con el programa
	listen(sockfd, BACKLOG); // escuchamos al puerto que asociamos

	addr_size = sizeof their_addr; 
	

	//esto esta mal
	int true = 1;
	while(true)
	{
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size); //reconocemos la existencia del cliente.
		if(new_fd == -1) true = 0;
	}
	msg = "Estamos conectados loqui";
	len = strlen(msg);
	bytes_sent = send(sockfd, msg, len, 0);

	return 0;
}
