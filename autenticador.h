#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>

void llenarStr(int socket, char *str, char *mostrar)
{
    memset(str,'\0',128);
    sistMensaje(socket,mostrar);
    recibir(socket, str);
}

int userLogin(int socket)//el servidor pide us y pass
{
    //tiene que venir "USER <nombreUsuario>\n"
    char user[128], passwd[128];
    llenarStr(socket, user, "username:");
    llenarStr(socket, passwd, "passwd:");
}

