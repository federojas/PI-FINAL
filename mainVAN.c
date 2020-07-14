#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treesADT.h"
#include "hoodADT.h"
#include <errno.h>

#define MAX_BUFFER 1024
#define TREE_N_HOOD_NAME_BUFFER 80

int main(int argc, char const *argv[]){
    if (argc != 3){
        fprintf(stderr, "Incorrect amount of arguments introduced\n");
        return EXIT_FAILURE;
    }
    
    treesADT tree = newTree();
    hoodADT hood = newHood();
    FILE *trees, *hoods,*query3VAN,*query1VAN,*query2VAN;
    trees = fopen(argv[1],"r");
    hoods=fopen(argv[2],"r");
    if (trees==NULL|| hoods==NULL) {
        fprintf(stderr, "Error in files input\n");
        return EXIT_FAILURE;
    }
    fseek (trees, 0, SEEK_END);
    fseek (hoods, 0, SEEK_END);
    int size1 = ftell(trees);
    int size2 = ftell(hoods);
    if(size1==0 || size2==0) {
        fprintf(stderr, "At least one of the files is empty\n");
        return EXIT_FAILURE;
    }
    fseek (trees, 0, SEEK_SET);
    fseek (hoods, 0, SEEK_SET);
    
    char *token;
    query1VAN=fopen("query1VAN.csv","w"); //the file is opened with "write" permissions so that it can be used to work
    query2VAN=fopen("query2VAN.csv","w"); 
    query3VAN=fopen("query3VAN.csv","w"); 
    

    char linesTrees[MAX_BUFFER],linesHoods[MAX_BUFFER];
    char treeName[TREE_N_HOOD_NAME_BUFFER], hoodName[TREE_N_HOOD_NAME_BUFFER];
    fgets(linesHoods, MAX_BUFFER, hoods); //the first lines of both .csv are skipped
    fgets(linesTrees, MAX_BUFFER, trees);
    int i;
    long pop;
    float diameter;
    fprintf(query1VAN,"neigbourhoods;trees Qty\n");
    fprintf(query2VAN,"neigbourhoods;trees/hab\n");
    fprintf(query3VAN,"tree name;diameter mean\n");

    //we already know that the hoods are in the third column, the tree name in the 7th and the diameter in the 12th 
    while(fgets(linesHoods, MAX_BUFFER, hoods)){
        token=strtok(linesHoods,";");//we already know that the first column goes for the hood and the second for the population
        strcpy(hoodName, token);
        token = strtok(NULL,";");
        pop = atol(token);
        if(pop > 0)
            addHood(hood, hoodName, pop);
    }

    while(fgets(linesTrees, MAX_BUFFER, trees))
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
        if(diameter > 0) // If the diameter is 0 then the diameter was not recorded in the database so we do not include the sample in our diameter average calculation
            addTree(tree, treeName, diameter);
        addTreeHood(hood, hoodName);
    }
    hoodList(hood);//we use the hoods present in the vector in order to create a list sorted by to criterias (trees per hood and amount of trees per habitant )  
    treeList(tree); //we use the trees names present in the vector of trees in order to create a list ordered  by the criteria diameter mean per tree spercies
    toBegin(tree);
    toBeginHoodHab(hood);
    toBeginQty(hood);
    int qty;

    while(hasNextHoodQty(hood)){
        nextHoodQty(hood, &qty, hoodName);
        fprintf(query1VAN,"%s;%d\n",hoodName,qty);
    }
      
    //query 1 goes for trees per hood - we need hood names and tree qty 
    //query 2 goes for amount of trees per habitant - we need hoods and trees
    //query 3 goes for diameter mean per tree spercies - we need tree name and diameter means 
    double treesPerHab;
    while(hasNextHoodHab(hood)){
        treesPerHab = nextHoodHab(hood,hoodName);
        fprintf(query2VAN,"%s;%g\n",hoodName, treesPerHab);
    }

    char name[TREE_N_HOOD_NAME_BUFFER];
    while(hasNext(tree)){
        diameter = next(tree, name);
        fprintf(query3VAN,"%s;%g\n", name, diameter);
    }

    fclose(query1VAN);
    fclose(query2VAN);
    fclose(query3VAN);
    fclose(trees);
    fclose(hoods);
    freeHood(hood);
    freeTree(tree);

    return EXIT_SUCCESS;
}