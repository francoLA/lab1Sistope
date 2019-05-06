#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

hijo* crearHijo()
{
    hijo *hijoActual = malloc(sizeof(hijo));
    hijoActual->pid = -1;
    return hijoActual;
}

datos *crearDato(){

    datos *nuevo = malloc(sizeof(datos));
}

int cantidadDatos(const char *nombreArchivo){

    FILE *archivo;
    int cantidad = 0;
    char aux[1000];
    archivo = fopen(nombreArchivo, "r");

    while(feof(archivo) == 0){
        fscanf(archivo, "%s", aux);
        cantidad ++;
    }

    fclose(archivo);

    return cantidad;
}

void leerArchivo(const char *nombreArchivo, datos *data[])
{
    FILE *archivo;
    archivo = fopen(nombreArchivo, "r");
    int cantidad = cantidadDatos(nombreArchivo);

    char aux2[50];
    char aux3[50];
    char aux4[50];
    char aux5[50];
    char aux6[50];

    for (int i = 0; i < cantidad; ++i)
    {
        datos *nuevo = crearDato();
        fscanf(archivo, " %[^','], %[^','], %[^','], %[^','], %s",aux2, aux3, aux4, aux5, aux6);
        sscanf(aux2, "%f", &nuevo -> u);
        sscanf(aux3, "%f", &nuevo -> v);
        sscanf(aux4, "%f", &nuevo -> real);
        sscanf(aux5, "%f", &nuevo -> imag);
        sscanf(aux6, "%f", &nuevo -> ruido);
        data[i] = nuevo;
    }

    fclose(archivo);

}

int main(int argc, char const *argv[])
{
    int cantidadHijos = 10;
    int cantidadDat = cantidadDatos(argv[1]);
    int pid;
    hijo* arregloHijos[cantidadHijos];
    datos* data[cantidadDat];
    leerArchivo(argv[1], data);

    printf("%f\n", data[5] -> ruido);

    int arregloEntrada[10] = {1,2,3,4,5,6,7,8,9,10};

    /*for(int i = 0 ; i < cantidadHijos;i++)
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
            for(int j = 0 ; j < i ; j++)
            {
                write(arregloHijos[i]->pipeB[WRITE],"Hola hijoA",100);
            }
        }
    }
    
    for(int i = 0 ; i < cantidadHijos;i++)
    {
        write(arregloHijos[i]->pipeB[WRITE],"FIN",100);
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
    }*/

    //Matar Hijos.
    
    return 0;
}
