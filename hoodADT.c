#include "hoodADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BLOCK 10
#define NO_MATCH 5

typedef struct tHood {
    char * hood_name;
    size_t habitants;
    size_t treeQty;
    float treesPerHab;
} tHood;

typedef struct hood {
    tHood hood;
    struct hood * tail;
} hoodNode;

typedef struct hoodCDT {
    hoodNode * firstHoodQty; // neighborhoods in descending order by qty, alphabetical order used to resolve draws
    hoodNode * firstHoodHab; // neighborhoods in descending order by qty/habitants, alphabetical order used to resolve draws
    tHood * vecHood; //vector containing all of the neighborhoods
    size_t vecSize;  //amount of neighborhoos in vector
    size_t vecDim;   //vector's real size
}hoodCDT;

typedef hoodCDT * hoodADT;

hoodADT newHood() {
    hoodADT hood;
    if((hood = calloc(1, sizeof(hoodCDT))) == NULL) {
        return NULL;
    }
    return hood;
}
//adds a neighborhood to the hood vector
int addHood(hoodADT hood, char * name, size_t habitants)
{
    if(hood->vecSize % BLOCK == 0)
    {
        hood->vecDim += BLOCK;
        hood->vecHood = realloc(hood->vecHood, hood->vecDim * sizeof(tHood) );
        if(hood->vecHood == NULL)
            return NO_MEM;   
    }
    hood->vecHood[hood->vecSize].hood_name = realloc(hood->vecHood[hood->vecSize].hood_name, (strlen(name)+1) * sizeof(char));
    if(hood->vecHood[hood->vecSize].hood_name == NULL)
        return NO_MEM;
    strcpy(hood->vecHood[hood->vecSize].hood_name, name);
    hood->vecHood[hood->vecSize].habitants = habitants;
    hood->vecHood[hood->vecSize].treeQty = 0;
    hood->vectSize += 1;
    return OK
}

//Adds the tree to the tree quantity of its neighborhood
int addTreeHood(hoodADT hood, char * hoodBelongs)
{
    for(int i = 0; i < hood->vecSize; i++)
    {
        int c = strcmp(hood->vecHood[i].hood_name, hoodBelongs);
        if(c == 0)
        {
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
        hood->vecHood[i].treesPerHab = (float)(trees/habitants);
    }
}

//function that sorts by descending order of trees per hab, creating a new node
static hoodNode * addRecHood(hoodNode * first, tHood hood, hoodNode * aux) {
    if (first == NULL || first->hood.treesPerHab < hood.treesPerHab) {
        hoodNode * result = malloc(sizeof(hoodNode));
        if (result == NULL) {
            return NULL;        
        }
        result->hood = hood;
        result->hood.hood_name = realloc(result->hood.hood_name, (strlen(hood.hood_name)+1) * sizeof(char));
        if (result->hood.hood_name == NULL)
            return NULL;
        strcpy(result->hood.hood_name, hood.hood_name);
        result->tail = first;
        aux = result;
        return result;
    }
    if (first->hood.treesPerHab == hood.treesPerHab) {
        if (strcmp(first->hood.hood_name, hood.hood_name) > 0) {
            hoodNode * result = malloc(sizeof(hoodNode));
        if (result == NULL) {
            return NULL;        
        }
        result->hood = hood;
        result->hood.hood_name = realloc(result->hood.hood_name, (strlen(hood.hood_name)+1) * sizeof(char));
        if (result->hood.hood_name == NULL)
            return NULL;
        strcpy(result->hood.hood_name, hood.hood_name);
        result->tail = first;
        aux = result;
        return result;
        }
    }
    first->tail = addRecHood(first->tail, hood, aux);
    return first;
}

int hoodList (hoodADT hood) {
    treesHab(hood); // we calculate the trees/hab
    for(int i = 0; i < hood->vecSize; i++)
    {
        hoodNode * aux; // node used to save the location of the newly created node
        hood->firstHoodHab = addRecHood(hood->firstHoodHab, hood->vecHood[i], aux);
        if (hood->firstHoodHab == NULL) {
            return NO_MEM;
        }
        hood->firstHoodQty = addRecQty(hood->firstHoodQty, aux); //HACER FUNCION QUE ORDENE POR CANT DE ARBOLES
        if (hood->firstHoodQty == NULL) {
            return NO_MEM;
        }
        free(hood->vecHood[i].hood_name);
    }
    free(hood->vecHood); // we free up no longer required memory
    hood->vecHood = NULL;
    return OK;
}


