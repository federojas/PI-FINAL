#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treesADT.h"
#include "hoodADT.h"
#include <errno.h>

#define ARG_ERR 0;
#define OK 1;

int main(int argc, char const *argv[]){
    if (argc!=3){
        printf("Incorrect amount of arguments introduced\n");
        return ARG_ERR;
    }
    
    treesADT  tree=newTree();
    hoodADT hood=newHood();
    FILE *trees, *hoods,*query3VAN,*query1VAN,*query2VAN;
    trees = fopen(argv[1],"r");
    hoods=fopen(argv[2],"r");
    if(trees==NULL|| hoods==NULL){
        printf("error in files input");
        return ARG_ERR;
    }
    fseek (trees, 0, SEEK_END);
    fseek (hoods, 0, SEEK_END);
    int size1 = ftell(trees);
    int size2 = ftell(hoods);
    if(size1==0 || size2==0){
        printf("at least one of the files is empty");
        return ARG_ERR;
    }
    fseek (trees, 0, SEEK_SET);
    fseek (hoods, 0, SEEK_SET);
    
    char *token;
    query1VAN=fopen("query1VAN.csv","w"); //the file is opened with "write" permissions so that it can be used to work
    query2VAN=fopen("query2VAN.csv","w"); //the file is opened with "write" permissions so that it can be used to work
    query3VAN=fopen("query3VAN.csv","w"); //the file is opened with "write" permissions so that it can be used to work
    

    char linesTrees[1024],linesHoods[1024];
    char treeName[80],hoodName[80];
    fgets(linesHoods,1024, hoods);//the first line is skipped
    fgets(linesTrees,1024, trees);//the first line is skipped 
    int i;
    long pop;
    float diameter;
    fprintf(query1VAN,"neigbourhoods;trees Qty\n");
    fprintf(query2VAN,"neigbourhoods;trees/hab\n");
    fprintf(query3VAN,"tree name;diameter mean\n");

    //we already know that the hoods are in the third column, the tree name in the 7th and the diameter in the 12th 
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
        for(i=0,token=strtok(linesTrees,";");i<16;i++)
        {
            if(i==12)
            {
                strcpy(hoodName,token);
            }
            if(i==6)
            {
                strcpy(treeName,token);

            }
            if(i==15)
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
        toBeginHoodHab(hood);
        toBeginQty(hood);
        int qty;

        while(hasNextHoodQty(hood)){
            nextHoodQty(hood, &qty, hoodName);
            fprintf(query1VAN,"%s;%d\n",hoodName,qty);
        }
      
        //query 1 es arboles por barrio - necesito barrios y cant de arboles 
        //query 2 es total de arboles por habitante - necesito barrios y arboles por hab
        //query 3 es diametro promedio por especie de arbol - necesito nombre del arbol y promedio del diametro 
        double TreesXHab;
        while(hasNextHoodHab(hood)){
           TreesXHab= nextHoodHab(hood,hoodName);
           fprintf(query2VAN,"%s;%g\n",hoodName,TreesXHab);
        }
        char name[100];
        while(hasNext(tree)){
            diameter=next(tree,name);
            fprintf(query3VAN,"%s;%g\n",name,diameter);
        }
        fclose(query1VAN);
        fclose(query2VAN);
        fclose(query3VAN);
        fclose(trees);
        fclose(hoods);
        freeHood(hood);
        freeTree(tree);
    return OK;
}