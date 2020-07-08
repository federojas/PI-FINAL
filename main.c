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
   // trees =fopen(argv[1],"r");
   neighborhoods=fopen(argv[1],"r");
    /*if(trees==NULL||neighborhoods== NULL)
    {
        printf("parameter error\n");
        return ARG_ERR;
    query1=fopen("query1.csv","w");
    query2=fopen("query2.csv","w");
    query3=fopen("query3.csv","w");
    }*/

    char asd[1000];
    //fgets(asd,100,trees);    ESTE SI VA    
    fgets(asd,1000,neighborhoods); //skip first line 
    /*printf("%s\n",asd);      
    char *token=strtok(asd,";\n\r\t");
    printf("%s\n",token)   ;
    token=strtok(NULL,";\n\r\t");
    printf("%s\n",token)   ;
    fgets(asd,1000,neighborhoods);
    token=strtok(asd,";\n\r\t");
    printf("%s\n",token)   ;
    token=strtok(NULL,";\n\r\t"); TODA ESTA PARTE NO VA
    printf("%s\n",token)   ;*/
        char *token;
    while(fgets(asd,1000,neighborhoods)){
        token=strtok(asd,";\n\t\r");
        int hood=atoi(token);
        token=strtok(NULL,";\n\r\t");
        int people=atoi(token);
        printf("%d\t%d\n",hood,people);

    }
    return OK;
}
