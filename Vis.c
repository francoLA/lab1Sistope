#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


typedef struct inputData
{
    
}datos;

datos* crearTabla()
{

}

int main(int argc, char const *argv[])
{
    char buffer[100] = "-1";
    int a = 0;
    int verificacion = 0;
    
    while(verificacion == 0)
    {
        read(STDIN_FILENO,buffer,100);
        a++;
        if(strncmp("EXIT",buffer,4) == 0)
        {
            verificacion = 1;
        }
    }
    char * num;

    sprintf(num, "%d", a);
    write(STDOUT_FILENO, num, 100);

    //Hijo entrega info.
    return 0;
}
