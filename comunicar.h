#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>


void sistMensaje(int puerto, char *msg)
{
    int len;
    len = strlen(msg);
    send(puerto, msg, len, 0);
}

int enviarMensaje(int puerto)
{
    int len;
    char buf[1024];
    scanf("%[^\n]",buf);
    getchar();
    len = strlen(buf);
    send(puerto, buf, len, 0);
    printf("Su mensaje, '%s', fue enviado con un largo de; %i\n", buf, len);
    memset(buf,0,1024);
    return len;
}

    
void recibir(int sock, char *buf)
{
    recv(sock, buf, 1024, 0);
    buf[strlen(buf)] = '\0';
}


void seguir(int new_fd, int ord)
{
    char buf[1024];
    int seguir = 1;
    while(1)
        {
            if(ord = 0) //0 SIGNIFICA QUE VENGO DEL SERVER
                {
                    enviarMensaje(new_fd);
                    recibir(new_fd,buf);
                    printf("%s\n",buf);
                }else
                {
                    recibir(new_fd,buf);
                    printf("%s\n",buf);
                    enviarMensaje(new_fd);
                }
            if(strcmp(buf,"quit") == 0)
                seguir = 0;
            memset(buf,0,1024);
        }
}
