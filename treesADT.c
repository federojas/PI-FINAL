#include "treesADT.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define BLOCK 100

typedef struct tTree {
    char * common_name; // scientific name
    float diameterSum; // sum of all database species diameters
    size_t qty; //amount of species specimens on data base
    float diameterMean; // average diameter of tree species
} tTree;

typedef struct tree {
    tTree tree;
    struct tree * tail;
} tree;

typedef struct treesCDT {
    tree * firstTree;   // trees in descending order by average species diameter, alphabetical order used to resolve draws
    tTree * treeVect; // Vector containing all of the tree species in the data base
    size_t vectSize; // amount of species in vector
    size_t vectDim; // amount of space in vector
} treesCDT;

typedef struct treesCDT * treesADT;

int addTree(treesADT tree, char * name, size_t diameter)
{ 
    for(int i = 0; i < tree->vectSize; i++)
    {
        if(strcmp(tree->treeVect[i].common_name, name) == 0)
        {
            tree->treeVect[i].qty += 1;
            tree->treeVect[i].diameterSum += diameter;
            return OK;
        }
    }
    if(vectDim % BLOCK == 0)
    {
        tree->vectDim += BLOCK;
        tree->treeVect = realloc(tree->treeVect, tree->vectDim * sizeof(tTree));
        if(tree->treeVect == NULL)
        {
            printf("No memory available\n");
            return NO_MEM;
        }
    }
    tree->treeVect[tree->vectSize].common_name = realloc(tree->treeVect[tree->vectSize].common_name, (strlen(name)+1)*sizeof(char));
    if(tree->treeVect[tree->vectSize].common_name == NULL)
    {
         printf("No memory available\n");
            return NO_MEM;        
    }
    strcpy(tree->treeVect[tree->vectSize].common_name, name);
    tree->treeVect[tree->vectSize].diameterSum = diameter;
    tree->treeVect[tree->vectSize].qty = 1;
    tree->vectSize += 1;
    return OK;
}

void diamAvg(treesADT tree) // calculates all of the species average diameters
{
    float diameter;
    float quantity;
    for(int i = 0; i < tree->vectSize; i++)
    {
        diameter = tree->treeVect[i].diameterSum;
        quantity = tree->treeVect[i].qty;
        tree->treeVect[i] = (float)(diameter / quantity);
    }
}

void treeList(treesADT tree)
{
    tree->treeVect = realloc(tree->treeVect, tree->vectSize * sizeof(tTree));
    if(tree->treeVect == NULL)
    {
         printf("No memory available\n");
            return NO_MEM;        
    }
    for(int i = 0; )
}

treesADT newTree() {
    treesADT tree;
    tree = calloc(1, sizeof(treesCDT));
    if(tree == NULL) {
        printf("No memory available\n");
        return NO_MEM;
    }
    return tree;
}
