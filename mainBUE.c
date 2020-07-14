#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treesADT.h"
#include "hoodADT.h"
#include <errno.h>

#define MAX_BUFFER 1024
#define TREE_NAME_BUFFER 80
#define HOOD_NAME_BUFFER 5

int main(int argc, char const *argv[]){
    if (argc != 3){
        fprintf(stderr, "Incorrect amount of arguments introduced\n");
        return EXIT_FAILURE;
    }
    
    treesADT tree = newTree();
    hoodADT hood = newHood();
    FILE *trees, *hoods,*query3BUE,*query1BUE,*query2BUE;
    trees = fopen(argv[1],"r");
    hoods = fopen(argv[2],"r");
    if (trees==NULL|| hoods==NULL) {
        fprintf(stderr, "Error in files input\n");
        return EXIT_FAILURE;
    }
    fseek (trees, 0, SEEK_END);
    fseek (hoods, 0, SEEK_END);
    int size1 = ftell(trees);
    int size2 = ftell(hoods);
    //printf("%d\n%d\n", size1, size2);
    if(size1==0 || size2==0){
        fprintf(stderr, "At least one of the files is empty\n");
        return EXIT_FAILURE;
    }
    fseek (trees, 0, SEEK_SET);
    fseek (hoods, 0, SEEK_SET);
    
    char *token;
    query1BUE=fopen("query1BUE.csv","w"); //the file is opened with "write" permissions so that it can be used to work
    query2BUE=fopen("query2BUE.csv","w"); //the file is opened with "write" permissions so that it can be used to work
    query3BUE=fopen("query3BUE.csv","w"); //the file is opened with "write" permissions so that it can be used to work
    

    char linesTrees[MAX_BUFFER],linesHoods[MAX_BUFFER];
    char treeName[TREE_NAME_BUFFER], hoodName[HOOD_NAME_BUFFER];
    fgets(linesHoods, MAX_BUFFER, hoods);   //the first line is skipped
    fgets(linesTrees, MAX_BUFFER, trees);   //the first line is skipped 

    long pop;
    float diameter;
    fprintf(query1BUE,"neigbourhoods;trees Qty\n");
    fprintf(query2BUE,"neigbourhoods;trees/hab\n");
    fprintf(query3BUE,"tree name;diameter mean\n");

    //we already know that the hoods are in the third column, the tree name in the 7th and the diameter in the 12th 
    while (fgets(linesHoods, MAX_BUFFER, hoods)) {
        token=strtok(linesHoods,";");//we already know that the first column goes for the hood and the second for the population
        strcpy(hoodName,token);
        token = strtok(NULL,";");
        pop = atol(token);
        if (pop > 0)
            addHood(hood, hoodName, pop);
    }

    int i;
    while (fgets(linesTrees, MAX_BUFFER, trees))
    {
        for(i=0, token=strtok(linesTrees,";"); i<12; i++)
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
        if(diameter > 0)
            addTree(tree, treeName, diameter);
        addTreeHood(hood, hoodName);
    }
        hoodList(hood);                
        treeList(tree);                
        toBegin(tree);
        toBeginHoodHab(hood);
        toBeginQty(hood);
        int qty;

        while(hasNextHoodQty(hood)) {
            nextHoodQty(hood, &qty, hoodName);
            fprintf(query1BUE,"%s;%d\n",hoodName,qty);
        }
      
        //query 1 es arboles por barrio - necesito barrios y cant de arboles 
        //query 2 es total de arboles por habitante - necesito barrios y arboles por hab
        //query 3 es diametro promedio por especie de arbol - necesito nombre del arbol y promedio del diametro 
        double treesPerHab;
        while(hasNextHoodHab(hood)){
           treesPerHab = nextHoodHab(hood,hoodName);
           fprintf(query2BUE, "%s;%.2g\n",hoodName, treesPerHab);

        }
        char name[TREE_NAME_BUFFER];
        while(hasNext(tree)){
            diameter=next(tree,name);
            fprintf(query3BUE,"%s;%g.2\n",name,diameter);
        }
        fclose(query1BUE);
        fclose(query2BUE);
        fclose(query3BUE);
        fclose(trees);
        fclose(hoods);
        freeHood(hood);
        freeTree(tree);

    return EXIT_SUCCESS;
}