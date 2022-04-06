#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#define BACKLOG 1 //numero de conexiones permitidas al mismo tiempo.

int autenticar(char *auten, char *str) //autenticar nos va a devolver 1 si existe el usuario y es la misma contraseña.
{
    if(strcmp(auten,str) == 0) 
        return 1;
    return 0;
}

int tok(char *user, char *pass) 
//tok linea a linea va a separa user:cs a user cs -> autent(user,contra);
{
    char string[256],auten[256];
    FILE *fp;
    strcpy(auten,user);
    strcat(auten,":");
    strcat(auten,pass);
    fp = fopen("users.txt", "r");
    for(fp;fp!=NULL;)
    {
        if(fgets(string, 60, fp) != NULL)
            if(autenticar(auten,string) == 1)
                return 1;
        else
            return 0;
    }
    return 0;
}

int userLogin(int socket)
{
    char user[128], passwd[128];
    memset(user,'\0',128);
    memset(passwd,'\0',128);
    sistMensaje(socket,"username:");
    recibir(socket, user);
    
    sistMensaje(socket,"\npassword");
    recibir(socket, passwd);
    return tok(user,passwd);
    //tok llamar
}

