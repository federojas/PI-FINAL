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
   
    if(size1==0 || size2==0){
        fprintf(stderr, "At least one of the files is empty\n");
        return EXIT_FAILURE;
    }
    fseek (trees, 0, SEEK_SET);
    fseek (hoods, 0, SEEK_SET);
    
    char *token;
    query1BUE=fopen("query1BUE.csv","w"); //the file is opened with "write" permissions so that it can be used to work
    query2BUE=fopen("query2BUE.csv","w");
    query3BUE=fopen("query3BUE.csv","w"); 
    

    char linesTrees[MAX_BUFFER],linesHoods[MAX_BUFFER];
    char treeName[TREE_NAME_BUFFER], hoodName[HOOD_NAME_BUFFER];
    fgets(linesHoods, MAX_BUFFER, hoods); //the first lines of both .csv are skipped
    fgets(linesTrees, MAX_BUFFER, trees);    

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
    hoodList(hood); //we use the hoods present in the vector in order to create a list sorted by to criterias (trees per hood and amount of trees per habitant )                
    treeList(tree); //we use the trees names present in the vector of trees in order to create a list ordered  by the criteria diameter mean per tree spercies         
    toBegin(tree);
    toBeginHoodHab(hood);
    toBeginQty(hood);
    int qty;

    while(hasNextHoodQty(hood)) {
        nextHoodQty(hood, &qty, hoodName);
        fprintf(query1BUE,"%s;%d\n",hoodName,qty);
    }
      
    //query 1 goes for trees per hood - we need hood names and tree qty 
    //query 2 goes for amount of trees per habitant - we need hoods and trees
    //query 3 goes for diameter mean per tree spercies - we need tree name and diameter means 
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