#include "treesADT.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node
{
    struct node * treeQtyTail; // tail to next neighborhood node by order of amount of trees per neighborhood
    struct node * treesPerHabTail; // tail to next neighborhood node by order of amount of trees per habitant
    char * name; // neighborhood name
    size_t treeQty; // amount of trees per neighborhood
    size_t treesPerHab; // amount of trees per habitant
}Neighborhood;

typedef struct node
{
    struct node * treeTail; // tail to next tree node
    char * name; // scientific name
    size_t diameterMean; // diameter average
}Tree;

typedef struct     
{
    Neighborhood * treeQtyFirst; // pointer to first node in descending order by quantity of trees
    Neighborhood * treePerHabFirst; // pointer to first node in descending order by amount of trees per habitant
    Tree * treeFirst; // pointer to first node in descending order by diamater average of a tree type
}treesCDT;

treesADT newTree()
{
    treesADT tree;
    if((tree = calloc(1,sizeof(treesCDT))) == NULL )
    {
        printf("No memory available");
        return no_mem;
    }
    return tree;
}

void freeRec(Neighborhood * hood, Tree * tree)
{
    if(hood != NULL && tree != NULL)
        freeRec(hood->treeQtyTail, tree->treeTail);
    if(hood == NULL && tree != NULL)
        freeRec(hood, tree->treeTail);
    if(hood != NULL && tree == NULL)
        freeRec(hood->treeQtyTail, tree);
    free(hood);
    free(tree);
}

void freeTrees(treesADT trees)
{
    freeRec(trees->treeQtyFirst, trees->treeFirst);
    free(trees);
}
