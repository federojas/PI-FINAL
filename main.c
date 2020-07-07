#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//we should include our adt.h later
#define OK 0
enum errors {arg_Err = 1, };

int main(int argc, char const *argv[])
{
    if(argc != 3)
    {
        printf("Incorrect amount of arguments.\n");
        return arg_Err;
    }
    // here we should initialize our adt 
    // we create the csv files
    FILE *trees, *neighborhoods, *query1,*query2, *query3;
    //we open the files to work 
    trees =fopen(argv[1],"r");
    neighborhoods=fopen(argv[2],"r");
    query1=fopen("query1.csv","w");
    query2=fopen("query2.csv","w");
    query3=fopen("query3.csv","w");

    return OK;
}
