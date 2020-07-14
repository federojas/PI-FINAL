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

//function that checks if there is available memory
static int availableMem (void) {
    if (errno != ENOMEM)
        return OK;
    perror("Error:");
    errno = 0;
    return !OK;
}

hoodADT newHood() {
    hoodADT hood;
    hood = calloc(1, sizeof(hoodCDT));
    if (!availableMem())
        return NULL;
    return hood;
}

//frees up the nodes
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

void freeVecHood (hoodADT hood) {
    for (size_t i = 0; i < hood->vecSize; i++) {
        free(hood->vecHood[i].hood_name);
    }
    free(hood->vecHood);
}

//adds a neighborhood to the hood vector
int addHood (hoodADT hood, char * name, size_t habitants) {
    if(hood->vecSize % BLOCK == 0) {
        hood->vecHood = realloc(hood->vecHood, (hood->vecSize + BLOCK) * sizeof(tHood));
        if (!availableMem())
            return !OK;
    }
    hood->vecHood[hood->vecSize].hood_name = malloc((strlen(name)+1) * sizeof(char));
    if (!availableMem())
        return !OK;
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
//if the amount of habitants in a neighborhood is cero then we set the trees / habitants as zero
static void treesPerHab(hoodADT hood)
{
    size_t habitants;
    size_t trees;
    for(int i = 0; i < hood->vecSize; i++) {
        habitants = hood->vecHood[i].habitants;
        trees = hood->vecHood[i].treeQty;
        double treesHab;
        if(habitants == 0)
            treesHab = 0;
        else 
            treesHab = ((int)(((double)trees/(double)habitants) * 100))/100.0; //this line calculates the trees/hab and truncates the result with two decimal places
        
        hood->vecHood[i].treesPerHab = treesHab;
    }
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
//if there is a memory error, first is returned so that the list doesn't break
//if a node is succesfuly created, added = 1
static hoodNode * addRec(hoodNode * first, tHood hood, hoodADT neighborhood, int * added){
    if (first == NULL || first->treesPerHab < hood.treesPerHab) {
        hoodNode * result = malloc(sizeof(hoodNode));
        if (!availableMem())
            return first;
        result->treeQty = hood.treeQty;
        result->treesPerHab = hood.treesPerHab;
        result->hood_name = malloc((strlen(hood.hood_name)+1) * sizeof(char));
        if (!availableMem()) {
            free(result);
            return first;
        }
        strcpy(result->hood_name, hood.hood_name);
        result->habTail = first;
        neighborhood->firstHoodQty = sortQty(neighborhood->firstHoodQty, result);
        *added = 1;
        return result;
    }
    if (first->treesPerHab == hood.treesPerHab) {
        if (strcmp(first->hood_name, hood.hood_name) > 0)
        {
            hoodNode * result = malloc(sizeof(hoodNode));
            if (!availableMem())
                return first;
            result->treeQty = hood.treeQty;
            result->treesPerHab = hood.treesPerHab;
            result->hood_name = malloc((strlen(hood.hood_name)+1) * sizeof(char));
            if (!availableMem()) {
                free(result);
                return first;
            }
            strcpy(result->hood_name, hood.hood_name);
            result->habTail = first;
            neighborhood->firstHoodQty = sortQty(neighborhood->firstHoodQty, result);
            *added = 1;
            return result;
        }
    }
    first->habTail = addRec(first->habTail, hood, neighborhood, added);
    return first;
}

//creates the hood list and frees up the hood vector
//if a node is succefully created, added = 1, if not added = 0
int hoodList (hoodADT hood) {
    treesPerHab(hood); // we calculate the trees/hab
    for(int i = 0; i < hood->vecSize; i++)
    {
        int added = 0;
        hood->firstHoodHab = addRec(hood->firstHoodHab, hood->vecHood[i], hood, &added); //sorts both queries creating only one list
        if(added == 0) //memory error
            return !OK;
        free(hood->vecHood[i].hood_name);          
    }
    free(hood->vecHood); // we free up no longer required memory from hood vector
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
        return !OK;
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

void nextHoodQty(hoodADT hood, int *cant, char *hoodName)
{
    if(hasNextHoodQty(hood) == 0)
        return;
    hoodNode * result = hood->currentHoodQty;
    strcpy(hoodName,result->hood_name);
    *cant=result->treeQty;
    hood->currentHoodQty = hood->currentHoodQty->qtyTail;
}