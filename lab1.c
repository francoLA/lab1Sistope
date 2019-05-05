#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ 0
#define WRITE 1

typedef struct nodoHijo
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
    /*
    int *pipes = (int * )malloc(2*sizeof(int));
    //Pipe de 1 via creado.
    pipe(pipes);
    printf("Pipes tiene los siguientes valores: %d, %d\n", 
		   pipes[LECTURA], pipes[ESCRITURA]);
    char stringEjemplo[10] = "hola";
    write(pipes[ESCRITURA], stringEjemplo, 10*sizeof(char));
    char *string2 = (char *)malloc(10*sizeof(char));
    string2[0] = '\0';
    int cuantoLeyo = read(pipes[LECTURA], string2, 10*sizeof(char));
    printf("Se leyó: %s\n", string2);
    
    if(fork() == 0)
    {
        close(pipes[LECTURA]);
        char *string3 = (char *)malloc(10*sizeof(char));
        string3[0] = '\0';
        strcpy(string3, "sustope!!");
        write(pipes[ESCRITURA], string3, 10*sizeof(char));
        printf("Hijo: Se escribió\n");
    }
    else
    {
        close(pipes[ESCRITURA]);
        int cuantoLeyo2 = read(pipes[LECTURA], string2, 10*sizeof(char));
        printf("Padre: Se leyó: %s\n", string2);
    }
    */
   /*
    
    int pipesOUT[cantidadHijos*2];
    int status;
    //int *pipesIN    = malloc(sizeof(int)*cantidadHijos*2);
    
    for(int i = 0 ; i < cantidadHijos; i++)
    {
        pipe(pipesOUT + i*2);
        //pipe(&pipesIN[2*i]);
    }
    for(int i = 0 ; i < cantidadHijos; i++)
    {
        dup2(pipesOUT[i*2+1],STDOUT_FILENO);
        close(pipesOUT[i*2]);

       // dup2(pipesIN[i*2],STDIN_FILENO);
       // close(pipesIN[i*2+1]);
    }
    */

    int cantidadHijos = 10;
    hijo* arregloHijos[cantidadHijos];

    int arregloEntrada[10] = {1,2,3,4,5,6,7,8,9,10};

    for(int i = 0 ; i < cantidadHijos;i++)
    {
        arregloHijos[i] = crearHijo();
        pipe(arregloHijos[i]->pipeA);
        pipe(arregloHijos[i]->pipeB);
        printf("%d,%d\n",arregloHijos[i]->pipeA[0],arregloHijos[i]->pipeA[1]);
    }

    char buffer[100];

    for(int i = 0 ; i < cantidadHijos;i++)
    {
        int pid = fork();
        if( pid == 0)
        {
            //Hijo
            /*
            char pipeA-0-I = arregloHijos[i]->pipeA[0];
            char pipeA-1-I = arregloHijos[i]->pipeA[1];
            char pipeB-0-I = arregloHijos[i]->pipeB[0];
            char pipeB-1-I = arregloHijos[i]->pipeB[1];
            char pipeA-0-S[3];
            char pipeA-1-S[3];
            char pipeB-0-S[3];
            char pipeB-1-S[3];
            */
            char num[100];
            sprintf(num, "%d", i);



            char *args[]= {"./vis",num,NULL};
            
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
            write(arregloHijos[i]->pipeB[WRITE],"Hola hijo",100);

            read(arregloHijos[i]->pipeA[READ], buffer, 100);

            printf("Padre: %s\n", buffer);
            //Padre
        }
    }
    return 0;
}
