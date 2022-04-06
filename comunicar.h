#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#define BACKLOG 1

void sistMensaje(int puerto, char *msg)
{
    int len;
    len = strlen(msg);
    send(puerto, msg, len, 0);
}

int enviarMensaje(int puerto)
{
    int len,er;
    char buf[1024];
    scanf("%[^\n]",buf);
    getchar();
    len = strlen(buf);
    er = send(puerto, buf, len, 0);
    memset(buf,0,1024);
    return er;
}

    
void recibir(int sock, char *buf)
{
    recv(sock, buf, 1024, 0);
    buf[strlen(buf)] = '\0';
}


struct addrinfo *setHints(char *dominio, char*puerto)
{
    struct addrinfo hints, *res;
    int rv;
    memset(&hints,0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;        //llenar ip
    rv = getaddrinfo(dominio,puerto, &hints, &res);
    return res;
}

int socketBindSv(char *puerto)
{
    struct addrinfo *p;
    int sock, rv;
    int yes = 1;

    p = setHints(NULL,puerto);

    
    for(p;p!=NULL;p = p->ai_next)
    {
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if(bind(sock,p->ai_addr, p->ai_addrlen) == -1)
            close(sock);
        break;
    }
    freeaddrinfo(p);
    listen(sock, BACKLOG); // escuchamos al puerto que asociamos
    return sock;
}

int conectar(char *puerto, char *dominio)
{
    int sock,rv;
    struct addrinfo *p;
    
    p = setHints(dominio,puerto);
    for(p; p != NULL; p = p->ai_next)
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

    freeaddrinfo(p);
    return sock;
}
