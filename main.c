#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//INCLUIR HOODADT.H Y TREESADT.H
#define OK 0 // poner en el .H
enum errors {ARG_ERR = 1, NO_MEM, }; // poner en el .H
/*
int main(int argc, char const *argv[])
{
   /* if(argc != 3)
    {
        printf("Incorrect amount of arguments.\n");
        return ARG_ERR;
    }*/
    // initialize ADT
    // the csv files are created
  //  FILE *trees, *neighborhoods, *query1,*query2, *query3;
    //the files needed are opened
   // trees =fopen(argv[1],"r");
   //neighborhoods=fopen(argv[1],"r");
    /*if(trees==NULL||neighborhoods== NULL)
    {
        printf("parameter error\n");
        return ARG_ERR;
    query1=fopen("query1.csv","w");
    query2=fopen("query2.csv","w");
    query3=fopen("query3.csv","w");
    }*/
/*
    char asd[100];
    //fgets(asd,100,trees);       
    fgets(asd,100,neighborhoods); 
    printf("%s\n",asd);      
    char *token;
    token=strtok(asd,";");
    //fgets(asd,100,neighborhoods)
    while(token!=NULL){
        printf("%s\n",token);
        int key=atoi(token);
        token=strtok(NULL,";");
        //printf("%d\n",key);
    }
    return OK;
}*/
int main(int argc, char const *argv[]){
    FILE *trees;
    trees=fopen(argv[1],"r");
    char lines[10000];
    fgets(lines,10000, trees);
    //me fijo en donde esta la columna con nombre de arboles 
    char *token;
    token=strtok(lines,"; ");
    //printf("%s\n",token);
   // token=strtok(NULL,";");
    //token=strtok(lines,"; ");

//    printf("%s\n",token);

    int count =0,salir=0;
    while(token!=NULL && !salir){
        if(strcmp("nombre_cientifico",token)==0)
        {
            printf("%s\t%d\n",token,count);
            salir=1;
        }else{
        count++;
        token=strtok(NULL,"; ");
        }
    }

}