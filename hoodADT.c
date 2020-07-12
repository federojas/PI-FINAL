#include "hoodADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define BLOCK 10
#define NO_MATCH 5
#define NO_MEM 0
#define OK 1
typedef struct tHood {
    char * hood_name;
    size_t habitants;
    size_t treeQty;
    float treesPerHab;
} tHood;

typedef struct hoodNode {
    char * hood_name;
    size_t treeQty;
    double treesPerHab;
    struct hoodNode * qtyTail;
    struct hoodNode * habTail;
} hoodNode;

typedef struct hoodCDT {
    hoodNode * firstHoodQty;        // neighborhoods in descending order by qty, alphabetical order used to resolve draws
    hoodNode * firstHoodHab;        // neighborhoods in descending order by qty/habitants, alphabetical order used to resolve draws
    hoodNode * currentHoodQty;
    hoodNode * currentHoodHab;
    tHood * vecHood;                //vector containing all of the neighborhoods
    size_t vecSize;                 //amount of neighborhoos in vector
} hoodCDT;

//typedef hoodCDT * hoodADT; //esto va en el .h ¿?

hoodADT newHood() {
    return calloc(1, sizeof(hoodCDT));
}
//adds a neighborhood to the hood vector
int addHood (hoodADT hood, char * name, size_t habitants) {
    if(hood->vecSize % BLOCK == 0) {
        hood->vecHood = realloc(hood->vecHood, (hood->vecSize + BLOCK) * sizeof(tHood));
    }
    hood->vecHood[hood->vecSize].hood_name = malloc((strlen(name)+1) * sizeof(char));
    strcpy(hood->vecHood[hood->vecSize].hood_name, name);
    hood->vecHood[hood->vecSize].habitants = habitants;
    hood->vecHood[hood->vecSize].treeQty = 0;
    hood->vecSize += 1;
    return OK;
}

//Adds the tree to the tree quantity of its neighborhood
int addTreeHood(hoodADT hood, char * treeHood)
{
    for(int i = 0; i < hood->vecSize; i++)
    {
        int c = strcmp(hood->vecHood[i].hood_name, treeHood);
        if (c == 0) {
            hood->vecHood[i].treeQty += 1;
            return OK;
        }
    }
    return NO_MATCH;
}

//aux function that calculates the amount of trees per habitant in each neighborhood
static void treesHab(hoodADT hood)
{
    size_t habitants;
    size_t trees;
    for(int i = 0; i < hood->vecSize; i++) {
        habitants = hood->vecHood[i].habitants;
        trees = hood->vecHood[i].treeQty;
        hood->vecHood[i].treesPerHab = ((double)trees/(double)habitants);
        //printf("%f\n", hood->vecHood[i].treesPerHab );
    }
}

static void freeRec(hoodNode *hood)
{
    if(hood == NULL)
        return ;
    freeRec(hood->habTail);
    free(hood->hood_name);
    free(hood);
}

void freeHood(hoodADT hood)
{
    freeRec(hood->firstHoodHab);
    free(hood);
}

//function that sorts by descending order of quantity of trees, without creating new nodes
static hoodNode * sortQty(hoodNode * first, hoodNode * sort) 
{
    if(first == NULL || first->treeQty < sort->treeQty)
    {
        sort->qtyTail = first;
        return sort;
    }
    if(first->treeQty == sort->treeQty)
    {
        int c = strcmp(first->hood_name, sort->hood_name);
        if(c > 0)
        {
            sort->qtyTail = first;
            return sort;
        }
    }
    first->qtyTail = sortQty(first->qtyTail, sort);
    return first;
}

//function that sorts by descending order of trees per hab, creating a new node and sorts the list by amount of trees per neighborhood without creating new nodes
static hoodNode * addRec(hoodNode * first, tHood hood, hoodADT neighborhood){
    if (first == NULL || first->treesPerHab < hood.treesPerHab) {
        hoodNode * result = malloc(sizeof(hoodNode));
        result->treeQty = hood.treeQty;
        result->treesPerHab = hood.treesPerHab;
        result->hood_name = malloc((strlen(hood.hood_name)+1) * sizeof(char));
        strcpy(result->hood_name, hood.hood_name);
        result->habTail = first;
        neighborhood->firstHoodQty = sortQty(neighborhood->firstHoodQty, result);
        return result;
    }
    if (first->treesPerHab == hood.treesPerHab) {
        if (strcmp(first->hood_name, hood.hood_name) > 0) {
            hoodNode * result = malloc(sizeof(hoodNode));
        result->treeQty = hood.treeQty;
        result->treesPerHab = hood.treesPerHab;
        result->hood_name = malloc((strlen(hood.hood_name)+1) * sizeof(char));
        strcpy(result->hood_name, hood.hood_name);
        result->habTail = first;
        neighborhood->firstHoodQty = sortQty(neighborhood->firstHoodQty, result);
        return result;
        }
    }
    first->habTail = addRec(first->habTail, hood, neighborhood);
    return first;
}

int hoodList (hoodADT hood) {
    treesHab(hood); // we calculate the trees/hab
    for(int i = 0; i < hood->vecSize; i++)
    {
        hood->firstHoodHab = addRec(hood->firstHoodHab, hood->vecHood[i], hood); //sorts both queries creating only one list
        free(hood->vecHood[i].hood_name);
    }
    free(hood->vecHood); // we free up no longer required memory
    hood->vecHood = NULL;
    return OK;
}

static void printList(hoodADT hood){
    hoodNode * aux=hood->firstHoodHab;
    while(aux!=NULL){
        printf("%s\t%ld\t%.2f\n",aux->hood_name, aux->treeQty, aux->treesPerHab);
        aux=aux->habTail;
    }
}

static void printList2(hoodADT hood){
    hoodNode * aux=hood->firstHoodQty;
    while(aux!=NULL){
        printf("%s\t%ld\n",aux->hood_name, aux->treeQty);
        aux=aux->qtyTail;
    }
}

void toBeginHoodHab(hoodADT hood){
    hood->currentHoodHab = hood->firstHoodHab;
}
int hasNextHoodHab(hoodADT hood){
    return hood->currentHoodHab != NULL;
}

// nextHoodHab(hoodADT hood)
// {
//     if(hasNextHoodHab(hood) == 0)
//         return NULL;
//     hoodNode * result = hood->currentHoodHab;
//     hood->currentHoodHab = hood->currentHoodHab->habTail;
//     return result;
// }

void toBeginQty(hoodADT hood){
    hood->currentHoodQty = hood->firstHoodQty;
}
int hasNextHoodQty(hoodADT hood){
    return hood->currentHoodQty != NULL;
}

void nextHoodQty(hoodADT hood, int *cant, char *hoodName)//me devuelve  trees per hab, el nombre del barrio y qty 
{
    if(hasNextHoodQty(hood) == 0)
        return;
    hoodNode * result = hood->currentHoodQty;
    strcpy(hoodName,result->hood_name);
    *cant=result->treeQty;
    hood->currentHoodQty = hood->currentHoodQty->qtyTail;
    
}

// int main(int argc, char const *argv[]){ //lo voy a hacer para bsas primero 
//      FILE *hoods,*trees;
//      char *token;
//      hoodADT hood=newHood();
//      hoods=fopen(argv[1],"r");
//      trees=fopen(argv[2],"r");
//      char linesHood[1024], linesTree[1024];
//      int i,habitantes;
//      char name[1024];
//      fgets(linesHood,1024,hoods);//skip the first line 
//      while(fgets(linesHood,1024,hoods)){
//          token=strtok(linesHood,";\r\t\n");
//         strcpy(name,token);
//         token=strtok(NULL,";\r\t\n");
//         habitantes=atoi(token);
//         addHood(hood,name,habitantes);
//     }
  
//     fgets(linesTree,1024,trees);//skip first line
//     token=strtok(linesTree,";\r\t\n");
//     while(fgets(linesTree,1024,trees)){
//         for(i=0, token=strtok(linesTree,";\r\t\n");i<3;i++){
//             if(i==2)
//                 strcpy(name,token);
//             token=strtok(NULL,";\r\t\n");
//         }
//         addTreeHood(hood,name);
//     }
//     // for(int i=0;i<15;i++)
//     // {
//     //    printf("%s\t%ld\n",hood->vecHood[i].hood_name,hood->vecHood[i].habitants);
//     // }
//     hoodList(hood);
//     printf("CANTIDAD DE ARBOLES/HABITANTE\n");
//     printList(hood);
//     printf("CANTIDAD DE ARBOLES\n");
//     printList2(hood);
//     //freeHood(hood);
// }