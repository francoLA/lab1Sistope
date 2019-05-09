#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <math.h>

#define FLOATMAX 20
#define BUFFERLECTURA 100

float mediaReal(datos* datos, float acumulador){
    float real = datos->real;
    return real + acumulador;
}
float medianaImaginaria(datos* datos, float acumulador){
    float imag = datos->imag;
    return imag + acumulador;
}
float ruidoTotal(datos* datos, float acumulador){
    float ruido = datos->ruido;
    return ruido + acumulador;
}
float potencia(datos* datos, float acumulador){
    float real = datos->real;
    float imag = datos->imag;
    float resultado = real*real + imag*imag;
    return sqrtf(resultado) + acumulador;
}

datos* crearTabla()
{
    datos *p_datos = malloc(sizeof(datos));
    p_datos->u = 0.0;
    p_datos->v = 0.0;
    p_datos->real = 0.0;
    p_datos->imag = 0.0;
    p_datos->ruido = 0.0;
    return p_datos;
}

void obtenerDato(datos* p_dato,int tipoDato, char*dato)
{
    if(tipoDato == 0){
        p_dato->u = strtof(dato,NULL);
    }
    else if(tipoDato == 1){
        p_dato->v = strtof(dato,NULL);
    }
    else if(tipoDato == 2){
        p_dato->real = strtof(dato,NULL);
    }
    else if(tipoDato == 3){
        p_dato->imag = strtof(dato,NULL);
    }
    else{
        p_dato->ruido = strtof(dato,NULL);
    }
}


datos* descifrarEntrada(datos* p_datos, char* entrada)
{
    char* dato = malloc(sizeof(char)*100); 
    dato = strtok(entrada,",");
    int contador = 0;
    //Ciclo que separa y analiza cada elemento de la linea en busca de palabras reservadas
    while(dato != NULL){
        obtenerDato(p_datos,contador,dato);
        contador++;               
        dato = strtok(NULL,",");
    }  
    free(dato);
    return p_datos;
}

char* cifrarSalida(float mediaReal, float medianaImg, float ruidoTotal, float potencia)
{
    char *datosCifrados = malloc(sizeof(char)*BUFFERLECTURA);
    char s_mediaReal[FLOATMAX];
    char s_medianaImg[FLOATMAX];
    char s_ruidoTotal[FLOATMAX];
    char s_potencia[FLOATMAX];

    gcvt(mediaReal, 7, s_mediaReal);
    gcvt(medianaImg, 7, s_medianaImg);
    gcvt(ruidoTotal, 7, s_ruidoTotal);
    gcvt(potencia, 7, s_potencia);

    strcat(datosCifrados,"Media real: ");
    strcat(datosCifrados,s_mediaReal);
    strcat(datosCifrados,"\nMedia imaginaria: ");
    strcat(datosCifrados,s_medianaImg);
    strcat(datosCifrados,"\nRuido total: ");
    strcat(datosCifrados,s_ruidoTotal);
    strcat(datosCifrados,"\nPotencia: ");
    strcat(datosCifrados,s_potencia);

    return datosCifrados;
}


int main(int argc, char const *argv[])
{
    datos* dato;
    int verificacion = 0;
    int cantidadVisibilidades = 0;
    float acumMedia = 0;
    float acumMediana = 0;
    float acumRuido = 0;
    float acumPoten= 0;
    datos *datos = crearTabla();
    
    while(verificacion == 0)
    {
        read(STDIN_FILENO,dato,sizeof(dato));
        /*
        if(strncmp("FIN",buffer,3) == 0){
            verificacion = 1;
            break;}
            */
        if(dato != NULL)
        {
            verificacion = 1;
            break;
        }
        /*
        datos = descifrarEntrada(datos, buffer);
        
        acumMedia = mediaReal(datos, acumMedia);
        acumMediana = medianaImaginaria(datos, acumMediana);
        acumRuido = ruidoTotal(datos, acumRuido);
        acumPoten = potencia(datos, acumPoten);
        */
        cantidadVisibilidades++;
    }
    //OJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOJOOJJOJOJOOJOJJOOJOJJOOJOJOJOJOJOJOJOJOJO
    //Agregar cantidadVisibilidades a acumMedia; acumMediana. => R/cantidadVisibilidades
    
    //Cifrar resultados y entregarlos al papa.
    char *salida;
    salida = cifrarSalida(acumMedia,acumMediana,acumRuido,acumPoten);
    write(STDOUT_FILENO, salida, 100);

    return 0;
}
