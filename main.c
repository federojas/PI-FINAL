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
    FILE *trees, *hoods,*query3,*query1,*query2;
    char *token;
    query1=fopen("query3.csv","w"); //we open the file with "write" permissions in order to work 
    query2=fopen("query3.csv","w"); //we open the file with "write" permissions in order to work 
    query3=fopen("query3.csv","w"); //we open the file with "write" permissions in order to work 
    trees = fopen(argv[1],"r");
    hoods=fopen(argv[2],"r");
    char linesTrees[1024],linesHoods[1024];
    char treeName[30],hoodName[5];
    fgets(linesHoods,1024, hoods);//we skip the first line 
    fgets(linesTrees,1024, trees);//we skip the first line 
    int i;
    long pop;
    float diameter;
    //we already know that the hoods are in the third column, the tree name in the 7th and the diameter in the 12th and
    while(fgets(linesHoods,1024, hoods)){
        token=strtok(linesHoods,";");//we already know that the first column goes for the hood and the second for the population
        strcpy(hoodName,token);
        token = strtok(NULL,";");
        pop = atol(token);
        if(pop != 0)
            addHood(hood,hoodName,pop);
        
    }

    while(fgets(linesTrees,1024, trees))
    {
        for(i=0,token=strtok(linesTrees,";");i<12;i++)
        {
            if(i==2)
            {
                strcpy(hoodName,token);
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
        if(diameter!=0)
            addTree(tree,treeName,diameter);
        addTreeHood(hood, hoodName);
    }
        hoodList(hood);
        vecToList(tree);
        toBegin(tree);
        
        char name[100];
        while(hasNext(tree)){
            diameter=next(tree,name);
            fprintf(query3,"%s;%f\n",name,diameter);
        }

    
    
}