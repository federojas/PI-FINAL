#include "hoodADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define BLOCK 10
#define NO_MATCH 2
#define OK 1

typedef struct tHood {
    char * hood_name; //neighborhood name
    size_t habitants; //neighborhood population
    size_t treeQty; //neighborhood tree quantity
    float treesPerHab; //amount of trees per habitant in neighborhood
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

/*int availableMem (void) {
    if (errno == ENOMEM) {
        perror("Error");
        errno = 0;
        return 1;
    }
    return 0;
}*/

hoodADT newHood() {
    hoodADT hood;
    hood = calloc(1, sizeof(hoodCDT));
    if (errno == ENOMEM) {
        perror("Error");
        errno = 0;
        return NULL;
    }
    return hood;
}
//adds a neighborhood to the hood vector
int addHood (hoodADT hood, char * name, size_t habitants) {
    if(hood->vecSize % BLOCK == 0) {
        hood->vecHood = realloc(hood->vecHood, (hood->vecSize + BLOCK) * sizeof(tHood));
        if (errno == ENOMEM) {
            perror("Error");
            errno = 0;
            return 0;
        }
    }
    hood->vecHood[hood->vecSize].hood_name = malloc((strlen(name)+1) * sizeof(char));
    if (errno == ENOMEM) {
        perror("Error");
        errno = 0;
        return 0;
    }
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
        float treesHab = floorf( ((double)trees/(double)habitants) * 100) / 100;
        hood->vecHood[i].treesPerHab = treesHab;
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
        if (c > 0)
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
        if (errno == ENOMEM) {
            perror("Error");
            errno = 0;
            return NULL;
        }
        result->treeQty = hood.treeQty;
        result->treesPerHab = hood.treesPerHab;
        result->hood_name = malloc((strlen(hood.hood_name)+1) * sizeof(char));
        if (errno == ENOMEM) {
            perror("Error");
            errno = 0;
            return NULL;
        }
        strcpy(result->hood_name, hood.hood_name);
        result->habTail = first;
        neighborhood->firstHoodQty = sortQty(neighborhood->firstHoodQty, result);
        return result;
    }
    if (first->treesPerHab == hood.treesPerHab) {
        if (strcmp(first->hood_name, hood.hood_name) > 0)
        {
            hoodNode * result = malloc(sizeof(hoodNode));
            if (errno == ENOMEM) {
            perror("Error");
            errno = 0;
            return NULL;
        }
            result->treeQty = hood.treeQty;
            result->treesPerHab = hood.treesPerHab;
            result->hood_name = malloc((strlen(hood.hood_name)+1) * sizeof(char));
            if (errno == ENOMEM) {
                perror("Error");
                errno = 0;
                return NULL;
            }
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
    return OK;
}


void toBeginHoodHab(hoodADT hood){
    hood->currentHoodHab = hood->firstHoodHab;
}
int hasNextHoodHab(hoodADT hood){
    return hood->currentHoodHab != NULL;
}

double nextHoodHab(hoodADT hood, char *hoodName)
{
    if(hasNextHoodHab(hood) == 0)
        return 0;
    hoodNode * result = hood->currentHoodHab;
    strcpy(hoodName,result->hood_name);
    double resp=result->treesPerHab;
    hood->currentHoodHab = hood->currentHoodHab->habTail;
    return resp;
}

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
