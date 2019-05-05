#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char buffer[100];

    read(STDIN_FILENO,buffer,100);
    write(STDOUT_FILENO, buffer, 100);

    //Hijo entrega info.
    return 0;
}
