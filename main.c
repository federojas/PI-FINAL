#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//include our ADT.h later
#define OK 0
enum errors {arg_Err = 1, };

int main(int argc, char const *argv[])
{
    if(argc != 3)
    {
        printf("Incorrect amount of arguments.\n");
        return arg_Err;
    }
    // initialize ADT
    // the csv files are created
    FILE *trees, *neighborhoods, *query1,*query2, *query3;
    //the files needed are opened
    trees =fopen(argv[1],"r");
    neighborhoods=fopen(argv[2],"r");
    query1=fopen("query1.csv","w");
    query2=fopen("query2.csv","w");
    query3=fopen("query3.csv","w");

    return OK;
}
