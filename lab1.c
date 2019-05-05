#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ 0
#define WRITE 1

typedef struct children
{
    int pipeA[2];
    int pipeB[2];
    int pid;
}hijo;

hijo* crearHijo()
{
    hijo *hijoActual = malloc(sizeof(hijo));
    hijoActual->pid = -1;
    return hijoActual;
}

int main(int argc, char const *argv[])
{
    int cantidadHijos = 10;
    int pid;
    hijo* arregloHijos[cantidadHijos];

    int arregloEntrada[10] = {1,2,3,4,5,6,7,8,9,10};

    for(int i = 0 ; i < cantidadHijos;i++)
    {
        arregloHijos[i] = crearHijo();
        pipe(arregloHijos[i]->pipeA);
        pipe(arregloHijos[i]->pipeB);
    }

    char buffer[100];

    for(int i = 0 ; i < cantidadHijos;i++)
    {
        pid = fork();
        if( pid == 0)
        {
            char num[100];
            char *args[]= {"./vis",NULL};
            
            dup2(arregloHijos[i]->pipeA[WRITE],STDOUT_FILENO);
            close(arregloHijos[i]->pipeA[READ]); 

            dup2(arregloHijos[i]->pipeB[READ],STDIN_FILENO);
            close(arregloHijos[i]->pipeB[WRITE]);
            
            //Entregandole por argumentos el numero de hijo.
            execvp("./vis", args);
        }
        else
        {
            //Lectura de cada salida de los hijos.
            write(arregloHijos[i]->pipeB[WRITE],"Hola hijoA",100);
            write(arregloHijos[i]->pipeB[WRITE],"Hola hijoB",100);
            write(arregloHijos[i]->pipeB[WRITE],"Hola hijoC",100);
            write(arregloHijos[i]->pipeB[WRITE],"EXIT",100);
            
        }
    }
    //Necesario?
        for(int i = 0 ; i < cantidadHijos;i++)
        {
            wait(NULL);
        }
        for(int i = 0 ; i < cantidadHijos;i++)
        {
            read(arregloHijos[i]->pipeA[READ], buffer, 100);
            printf("Padre: %s\n", buffer);
        }    
        for(int i = 0 ; i < cantidadHijos;i++)
        {
            close(arregloHijos[i]->pipeA[WRITE]);
            close(arregloHijos[i]->pipeA[READ]);
            close(arregloHijos[i]->pipeB[WRITE]);
            close(arregloHijos[i]->pipeB[READ]);
        }
    
    return 0;
}
