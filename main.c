#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//include our ADT.h later
#define OK 0 // poner en el .H
enum errors {ARG_ERR = 1, NO_MEM, }; // poner en el .H

int main(int argc, char const *argv[])
{
   /* if(argc != 3)
    {
        printf("Incorrect amount of arguments.\n");
        return ARG_ERR;
    }*/
    // initialize ADT
    // the csv files are created
    FILE *trees, *neighborhoods, *query1,*query2, *query3;
    //the files needed are opened
    trees =fopen(argv[1],"r");
    neighborhoods=fopen(argv[2],"r");
    if(trees==NULL||neighborhoods== NULL)
    {
        printf("parameter error\n");
        return ARG_ERR;
    }
    query1=fopen("query1.csv","w");
    query2=fopen("query2.csv","w");
    query3=fopen("query3.csv","w");

    char asd[100];
    //fgets(asd,100,trees);       
    fgets(asd,100,neighborhoods); 
    printf("%s\n",asd);      
    return OK;
}
