#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
char* separar(char *str)
{
    char *tok;
    tok = strtok(str," ");
    tok = strtok(NULL, " ");
    return tok;
}


int toks(char *user, char*passwd)
{
    char temp[256];
    memset(temp, '\0', 256);
    user = separar(user);
    passwd = separar(passwd);
    strcat(temp,user);
    strcat(temp,":");
    strcat(temp,passwd);
    strcat(temp,"\n");

    return compareEnFile(temp);   
}


int autenticar(char *comparar, char* registrado)
{
    if(strcmp(comparar,registrado) == 0)
        return 1;
    else return 0;
}

int compareEnFile(char *userAComparar)
{
    char userRegistrado[256];
    FILE *fp;
    fp = fopen("ftpusers","r");
    for(fp;fp!=NULL;)
    {
        if(fgets(userRegistrado, 256, fp) != NULL)
        {
            if(autenticar(userAComparar, userRegistrado))
            return 1;
        }
    }
       
    fclose(fp);
    return 0;
}

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
    llenarStr(socket, user, "220");
    llenarStr(socket, passwd, "331");
    return toks(user,passwd);
}

