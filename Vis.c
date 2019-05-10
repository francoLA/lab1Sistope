#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <math.h>

#define FLOATMAX 20
#define BUFFERLECTURA 100

// -Descripcion: De los datos de entrada se obtiene el dato real para luego sumarlo con un acumulador y retornarlo.
// -Entradas: Datos de entrada, flotante acumulador
// -Salidas: Flotante del calculo de media real
float mediaReal(datos* datos, float acumulador){
    float real = datos->real;
    return real + acumulador;
}

// -Descripcion: De los datos de entrada se obtiene el dato real para luego sumarlo con un acumulador y retornarlo.
// -Entrada: Datos de entrada, flotante acumulador
// -Salida: Flotante del calculo de mediana imaginaria
float medianaImaginaria(datos* datos, float acumulador){
    float imag = datos->imag;
    return imag + acumulador;
}

// -Descripcion: De los datos de entrada se obtiene el dato real para luego sumarlo con un acumulador y retornarlo.
// -Entrada: Datos de entrada, flotante acumulador
// -Salida: Flotante del calculo de ruido total
float ruidoTotal(datos* datos, float acumulador){
    float ruido = datos->ruido;
    return ruido + acumulador;
}

// -Descripcion: De los datos de entrada se obtiene el dato real e imaginario para procesarlo, y luego retornarlo.
// -Entrada: Datos de entrada, flotante acumulador
// -Salida: Flotante del calculo de la potencia
float potencia(datos* datos, float acumulador){
    float real = datos->real;
    float imag = datos->imag;
    float resultado = real*real + imag*imag;
    return sqrtf(resultado) + acumulador;
}

// -Descripcion: Inicializa y asigna memoria a la estructura datos
// -Entrada: -
// -Salida: Puntero a una tabla de datos
datos* crearTabla(){
    datos *p_datos = malloc(sizeof(datos));
    p_datos->u = 0.0;
    p_datos->v = 0.0;
    p_datos->real = 0.0;
    p_datos->imag = 0.0;
    p_datos->ruido = 0.0;
    return p_datos;
}

// -Descripcion: A razon del tipo de dato entrado, se procedera a transformar el string de entrada en uno de los
//               posibles datos, para luego almacenarlo.
// -Entrada: Puntero a una tabla de datos, entero que indica un tipo del mismo, y un char del dato tipo string
// -Salida: -
void obtenerDato(datos* p_dato,int tipoDato, char*dato){
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

// -Descripcion: La funcion toma el string de entrada y separa sus segmentos en busca de los valores de la tabla de datos.
// -Entrada: Puntero a una tabla de dato y un string que posee la informacion de entrada.
// -Salida: Puntero a una tabla de datos.
datos* descifrarEntrada(datos* p_datos, char* entrada){
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

// -Descripcion: Esta se encarga de transformar todos los resultados a string, para luegos traspasarlo a un string, dandoles en el
//               en proceso la estructura de salida solicitada.
// -Entrada: Floatantes de los resultados (media real, mediana imaginaria, ruido total, potencia y cantidad de visibilidades) y un
//           string que indica a cual disco pertenece los resultados.
// -Salida: String que contiene todos los elementos listos para imprimir.
char* cifrarSalida(float mediaReal, float medianaImg, float ruidoTotal, float potencia,int cantidadVisibilidades,char* numeroDisco){
    char *datosCifrados = malloc(sizeof(char)*BUFFERLECTURA);
    char s_mediaReal[FLOATMAX];
    char s_medianaImg[FLOATMAX];
    char s_ruidoTotal[FLOATMAX];
    char s_potencia[FLOATMAX];
    char s_cantidadVisibilidades[FLOATMAX];
    char s_pid[FLOATMAX];
    char s_numeroDisco[FLOATMAX];
    sprintf(s_cantidadVisibilidades, "%d", cantidadVisibilidades);
    sprintf(s_pid, "%d", getpid());
    gcvt(mediaReal, 7, s_mediaReal);
    gcvt(medianaImg, 7, s_medianaImg);
    gcvt(ruidoTotal, 7, s_ruidoTotal);
    gcvt(potencia, 7, s_potencia);
    strcat(datosCifrados,"Disco: ");
    strcat(datosCifrados,numeroDisco);
    strcat(datosCifrados,"\nMedia real: ");
    strcat(datosCifrados,s_mediaReal);
    strcat(datosCifrados,"\nMedia imaginaria: ");
    strcat(datosCifrados,s_medianaImg);
    strcat(datosCifrados,"\nRuido total: ");
    strcat(datosCifrados,s_ruidoTotal);
    strcat(datosCifrados,"\nPotencia: ");
    strcat(datosCifrados,s_potencia);
    strcat(datosCifrados,"\n@Soy el hijo de pid ");
    strcat(datosCifrados,s_pid);
    strcat(datosCifrados,", procesé ");
    strcat(datosCifrados,s_cantidadVisibilidades);
    strcat(datosCifrados," visibilidades\n");
    return datosCifrados;
}

// -Descripcion: Funcion principal del hijo, esta se encarga de recibir la informacion del padre, para proceder a realizar los calculos
//               solicitados. Al final del proceso le retorna los resultados al hijo.
// -Entrada: Argumentos de entrada y el largo del mismo.
// -Salida: Entero que indica si el proceso finalizo correctamente o no.
int main(int argc, char const *argv[]){
    int verificacion = 0;
    int cantidadVisibilidades = 0;
    float acumMedia = 0;
    float acumMediana = 0;
    float acumRuido = 0;
    float acumPoten= 0;
    datos* dato = crearTabla();
    char buffer[100];
    
    while(verificacion == 0){
        read(STDIN_FILENO,buffer,BUFFERLECTURA);
        if(strncmp("FIN",buffer,3) == 0){
            verificacion = 1;
            break;
        }
        dato = descifrarEntrada(dato, buffer);
        acumMedia = mediaReal(dato, acumMedia);
        acumMediana = medianaImaginaria(dato, acumMediana);
        acumRuido = ruidoTotal(dato, acumRuido);
        acumPoten = potencia(dato, acumPoten);
        cantidadVisibilidades++;
    }

    if(acumMedia != 0 ){acumMedia = acumMedia / cantidadVisibilidades;}
    if(acumMediana != 0){acumMediana = acumMediana / cantidadVisibilidades;}
    char *salida;

    read(STDIN_FILENO,buffer,BUFFERLECTURA);
    salida = cifrarSalida(acumMedia,acumMediana,acumRuido,acumPoten,cantidadVisibilidades,buffer);
    free(dato);
    write(STDOUT_FILENO, salida, 200);
    
    return 0;
}
