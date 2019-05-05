#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    write(STDOUT_FILENO, argv[1], 33);

    //Hijo entrega info.
    return 0;
}
