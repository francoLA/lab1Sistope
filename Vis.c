#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct inputData
{
    int u;
    int v;
    int real;
    int imag;
    int ruido;
}datos;

int mediaReal(datos* datos, int acumulador){return datos->real + acumulador;}
int medianaImaginaria(datos* datos, int acumulador){return datos->imag + acumulador;}
int ruidoTotal(datos* datos, int acumulador){return datos->ruido + acumulador;}
int potencia(datos* datos, int acumulador){
    int resultadoA = (datos->real^2 + datos->imag^2)^(1/2);
    return resultadoA + acumulador;
}

datos* crearTabla()
{
    datos *p_datos = malloc(sizeof(datos));
    return p_datos;
}

datos* descifrarEntrada(datos* p_datos, char* entrada)
{
    return p_datos;
}

char* cifrarSalida(int mediaReal, int medianaImag, int ruidoTotal, int potencia)
{
    return "hola";
}


int main(int argc, char const *argv[])
{
    char buffer[100];
    int verificacion = 0;
    int cantidadVisibilidades = 0;
    int acumMedia = 0;
    int acumMediana = 0;
    int acumRuido = 0;
    int acumPoten= 0;
    datos *datos = crearTabla();
    
    while(verificacion == 0)
    {
        read(STDIN_FILENO,buffer,100);
        if(strncmp("FIN",buffer,3) == 0){
            verificacion = 1;
            break;}
        datos = descifrarEntrada(datos, buffer);
        cantidadVisibilidades++;
        //Funciones de calculo con los datos
    }

    //Agrenar cantidadVisibilidades a acumMedia; acumMediana. => R/cantidadVisibilidades

    //Cifrar resultados y entregarlos al papa.
    char * num;

    sprintf(num, "%d", a);
    write(STDOUT_FILENO, num, 100);

    return 0;
}
