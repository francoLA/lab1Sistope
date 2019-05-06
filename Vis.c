#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

float mediaReal(datos* datos, float acumulador){return datos->real + acumulador;}
float medianaImaginaria(datos* datos, float acumulador){return datos->imag + acumulador;}
float ruidoTotal(datos* datos, float acumulador){return datos->ruido + acumulador;}
float potencia(datos* datos, float acumulador){
    float resultadoA = (int)(datos->real*datos->real + datos->imag*datos->imag)^(1/2);
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

char* cifrarSalida(float mediaReal, float medianaImag, float ruidoTotal, float potencia)
{
    return "hola";
}


int main(int argc, char const *argv[])
{
    char buffer[100];
    int verificacion = 0;
    int cantidadVisibilidades = 0;
    float acumMedia = 0;
    float acumMediana = 0;
    float acumRuido = 0;
    float acumPoten= 0;
    datos *datos = crearTabla();
    
    while(verificacion == 0)
    {
        read(STDIN_FILENO,buffer,100);
        if(strncmp("FIN",buffer,3) == 0){
            verificacion = 1;
            break;}
        //xdatos = descifrarEntrada(datos, buffer);
        cantidadVisibilidades++;
        //Funciones de calculo con los datos
    }

    //Agrenar cantidadVisibilidades a acumMedia; acumMediana. => R/cantidadVisibilidades

    //Cifrar resultados y entregarlos al papa.
    char * num;

    sprintf(num, "%d", cantidadVisibilidades);
    write(STDOUT_FILENO, num, 100);

    return 0;
}
