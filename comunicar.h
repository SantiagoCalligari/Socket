#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
 

int enviarMensaje(int puerto)
{
    int len;
    char buf[1024];
    scanf("%[^\n]",buf);
    len = sizeof(buf);
    send(puerto, buf, len, 0);
    printf("Su mensaje, '%s', fue enviado\n", buf);
    return len;
}

    
void recibir(int sock)
{
    char buf[1024];
    recv(sock, buf, 1024, 0);
    buf[sizeof(buf)] = '\0';
    printf("Su mensaje es; %s\n",buf);
}
