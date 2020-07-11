#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "treesADT.h"
#include "hoodADT.h"
//INCLUIR HOODADT.H Y TREESADT.H
#define OK 0 // poner en el .H
//(este es el main de buenos aires) 
enum errors {ARG_ERR = 1, NO_MEM, }; // poner en el .H
int main(int argc, char const *argv[]){
    // if (argc!=3){ ESTA PARTE VA CUANDO YA ANDEN LOS DOS .H Y MANDEMOS LOS DOS CSV
    //     printf("cantidad de argumentos incorrecta\n");
    //     return ARG_ERR;
    // }
    treesADT  tree=newTree();
    hoodADT hood=newHood();
    //primero voy a hacer la parte del query3 que es la que ya ta lista
    FILE *trees, *query3;
    char *token;
    query3=fopen("query3.csv","w"); //we open the file with "write" permissions in order to work 
    trees = fopen(argv[1],"r");
    char lines[1024];
    char treeName[30],hood[5];
    fgets(lines,1024, trees);//we skip the first line 
    int i,diameter;
    //we already know that the hoods are in the third column, the tree name in the 7th and the diameter in the 12th and
    while(fgets(lines,1024, trees))
    {
        for(i=0,token=strtok(lines,";");i<12;i++)
        {
            if(i==2)
            {
                strcpy(hood,token);
            }
            if(i==7)
            {
                strcpy(treeName,token);
            }
            if(i==11)
            {
                diameter=atoi(token);
            }
            token=strtok(NULL,";");
        }
        if(diametro!=0)
            addTree(tree,name,diametro);
    }
        vecToList(tree);
        //printList(tree);
        //freeTree(tree);
    }
    // int size=hoodAmount(tree);
    // for(int i=0,i<size;i++ ){

    // }
    
}