#include <stdio.h>
#include <stdlib.h>

#define OK 0
enum errors {arg_Err = 1, };

int main(int argc, char const *argv[])
{
    if(argc != 3)
    {
        printf("Incorrect amount of arguments.\n");
        return arg_Err;
    }
    return OK;
}
