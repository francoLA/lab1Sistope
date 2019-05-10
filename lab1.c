#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

#define READ 0
#define WRITE 1
#define NUMEROENTRADAS 5
#define BUFFERLECTURA 100
#define FLOATMAX 20

char* parametros[NUMEROENTRADAS] = {"-i","-o","-n","-d","-b"};

// -Descripcion:  Crea un nuevo dato del tipo hijo.
// -Enntardas: -
// -Salidas: un nuevo dato de tipo hijo.

hijo* crearHijo()
{
    hijo *p_hijo = malloc(sizeof(hijo));
    p_hijo->pid = -1;
    return p_hijo;
}

// -Descripcion:  Crea un nuevo dato del tipo entrada.
// -Enntardas: -
// -Salidas: un nuevo dato de tipo entrada.

entrada* crearEntrada()
{
    entrada *p_entrada = malloc(sizeof(entrada));
    p_entrada->archivoV = "null";
    p_entrada->archivoS = "null";
    p_entrada->ancho = -1;
    p_entrada->ndiscos = -1;
    p_entrada->bandera = 0;
    return p_entrada;
}

// -Descripcion:  Crea un nuevo dato del tipo datos.
// -Enntardas: -
// -Salidas: un nuevo dato de tipo datos.

datos *crearDato(){
    datos *nuevo = malloc(sizeof(datos));
    return nuevo;
}

// -Descripcion: Calcula la cantidad de datos en el archivo de entrada.
// -Enntardas: const char *nombreArchivo
// -Salidas: un entero correspondiente a la cantidad de datos.

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

// -Descripcion: Realiza la lectura del archivo de entrada y guarda los datos en un arreglo del tipo datos.
// -Enntardas: const char *nombreArchivo, datos *data[]
// -Salidas: -.

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

// -Descripcion: Se encarga de verificar las entradas necesarias para la ejecucion del programa.
// -Enntardas: int argc,char const *argv[]
// -Salidas: Un nuevo tipo de dato entrada.

entrada* analizarEntradas(int argc,char const *argv[])
{
    entrada *p_entrada = crearEntrada();
    if(argc < 9){
        printf("Faltan parametros, verifique los datos de entrada\n");
        exit(0);
    }
    else if(argc > 10){
        printf("Demasiados parametros, verifique los datos de entrada\n");
        exit(0);        
    }
    else{
        for(int i = 1; i < argc ; i++){
            for(int j = 0; j < NUMEROENTRADAS;j++){
                char* tipoEntrada = parametros[j];
                if(strncmp(tipoEntrada,argv[i],2) == 0){
                    if(j == 0){p_entrada->archivoV = argv[i+1];}
                    else if(j == 1){p_entrada->archivoS = argv[i+1];}
                    else if(j == 2){p_entrada->ndiscos = atoi(argv[i+1]);}
                    else if(j == 3){p_entrada->ancho = atoi(argv[i+1]);}
                    else {p_entrada->bandera = 1;}
                }
            }
        }
        if(p_entrada->ancho == -1 ||p_entrada->ndiscos == -1 || strncmp(p_entrada->archivoV,"null",3) == 0 || strncmp(p_entrada->archivoS,"null",3) == 0){
            printf("Faltan parametros, verifique los datos de entrada\n");
            exit(0);
        }
        else {return p_entrada;}
    }
}

// -Descripcion: Calcula la distancia de un dato determinado.
// -Enntardas: datos* datos.
// -Salidas: Un dato de tipo float correspondiente a la distancia calculada.

float distanciaVisibilidad(datos *datos)
{
    float u = datos->u;
    float v = datos->v;
    float resultado = u*u + v*v;
    return sqrtf(resultado);
}

// -Descripcion: Concatena dos strings y agrega una coma al final.
// -Enntardas: char* a, char* b.
// -Salidas: -.

void concatenarString(char* a, char* b)
{
    strcat(a, b);
    strcat(a,",");
}

// -Descripcion: Cifra los datos para poder entregarlos al hijo.
// -Enntardas: datos *datos.
// -Salidas: Una cadena de caracteres correspondiente a los datos.

char* cifrarDatos(datos *datos)
{
    char *datosCifrados = malloc(sizeof(char)*BUFFERLECTURA);
    char u[FLOATMAX];
    char v[FLOATMAX];
    char real[FLOATMAX];
    char imag[FLOATMAX];
    char ruido[FLOATMAX];
    gcvt(datos->u, 7, u);
    gcvt(datos->v, 7, v);
    gcvt(datos->real, 7, real);
    gcvt(datos->imag, 7, imag);
    gcvt(datos->ruido, 7, ruido);
    concatenarString(datosCifrados,u);
    concatenarString(datosCifrados,v);
    concatenarString(datosCifrados,real);
    concatenarString(datosCifrados,imag);
    strcat(datosCifrados,ruido);
    return datosCifrados;
}

// -Descripcion: Se encarga de verificar las entradas necesarias para la ejecucion del programa.
// -Enntardas: int argc,char const *argv[]
// -Salidas: Un nuevo tipo de dato entrada.

void posicionarDatos(int cantidadDat, datos* data[], hijo* arregloHijos[], entrada* entradas){

    for(int i = 0 ; i < cantidadDat;i++)
    {
        datos* dato = data[i];
        float distancia = distanciaVisibilidad(dato);
        float limInferior = 0;
        float limSuperior = entradas -> ancho;
        int datoPosicionado = 0;
        int discoDelDato = 0;
        //Funcion para posicionar.

        while(datoPosicionado == 0)
        {
            if( (limInferior <= distancia && limSuperior > distancia) || discoDelDato == entradas -> ndiscos-1)
            {
                char* datosCifrados = cifrarDatos(dato);
                write(arregloHijos[discoDelDato]->pipeB[WRITE],datosCifrados,100);
                datoPosicionado = 1;
            }
            else
            {
                limInferior = limSuperior;
                limSuperior = limSuperior + entradas -> ancho;
                discoDelDato++;
            }
        } 
    }
}

// -Descripcion: Escribe los resultados del programa en el archivo de salida.
// -Enntardas: entrada* entradas, int cantidadHijos, hijo* arregloHijos[].
// -Salidas: -.

void escribirSalida(entrada* entradas, int cantidadHijos, hijo* arregloHijos[]){

    char buffer[300];

    FILE *file = fopen(entradas->archivoS,"w");

    for(int i = 0 ; i < cantidadHijos;i++)
    {
        read(arregloHijos[i]->pipeA[READ], buffer, 300);
        char *palabra = strtok(buffer,"@");
        fputs(palabra,file);
        palabra = strtok(NULL,"@");
        if(entradas->bandera == 1){printf("%s",palabra);}
    }    
    
    fclose(file);
}

// -Descripcion: Crea los hijos para realizar los calculos de un disco.
// -Enntardas: int cantidadHijos, hijo* arregloHijos[].
// -Salidas: -.

void crearHijos(int cantidadHijos, hijo* arregloHijos[]){

    int pid;

    for(int i = 0 ; i < cantidadHijos;i++)
    {
        pid = fork();
        if( pid == 0)
        {
            char *args[]= {"./vis",NULL};
            dup2(arregloHijos[i]->pipeA[WRITE],STDOUT_FILENO);
            close(arregloHijos[i]->pipeA[READ]); 
            //close(arregloHijos[i]->pipeA[WRITE]);

            dup2(arregloHijos[i]->pipeB[READ],STDIN_FILENO);
            close(arregloHijos[i]->pipeB[WRITE]);
            //close(arregloHijos[i]->pipeB[READ]);
            
            execvp(args[0], args);
        }
    }
}

int main(int argc, char const *argv[])
{
    entrada* entradas = analizarEntradas(argc, argv);
    int cantidadHijos = entradas->ndiscos;
    const char* nombreArchivo = entradas->archivoV;
    int cantidadDat = cantidadDatos(nombreArchivo);
    hijo* arregloHijos[cantidadHijos];

    datos* data[cantidadDat];
    leerArchivo(nombreArchivo, data);

    for(int i = 0 ; i < cantidadHijos;i++){
        arregloHijos[i] = crearHijo();
        pipe(arregloHijos[i]->pipeA);
        pipe(arregloHijos[i]->pipeB);
    }

    //Creacoion de los procesos hijos.
    crearHijos(cantidadHijos, arregloHijos);
    
    //Proceso asignacion de hijos.
    posicionarDatos(cantidadDat, data, arregloHijos, entradas);

    //Matar hijos
    for(int i = 0 ; i < cantidadHijos;i++)
    {
        write(arregloHijos[i]->pipeB[WRITE],"FIN",100);
        wait(NULL);
    }

    escribirSalida(entradas, cantidadHijos, arregloHijos);

    //Cerrar pipes
    for(int i = 0 ; i < cantidadHijos;i++)
    {
        close(arregloHijos[i]->pipeA[WRITE]);
        close(arregloHijos[i]->pipeA[READ]);
        close(arregloHijos[i]->pipeB[WRITE]);
        close(arregloHijos[i]->pipeB[READ]);
    }

    return 0;
}
