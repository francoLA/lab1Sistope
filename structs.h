//////definicion de estructuras////////

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct children
{
    int pipeA[2];
    int pipeB[2];
    int pid;
}hijo;

typedef struct inputData
{
    float u;
    float v;
    float real;
    float imag;
    float ruido;
}datos;


#endif