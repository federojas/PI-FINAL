#include "treesADT.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct tTree {
    char * common_name; // scientific name
    size_t diameter;
    size_t qty;
    size_t diameterMean; // average diameter of tree species
} tTree;

typedef struct tree {
    tTree tree;
    struct tree * tail;
} tree;

typedef struct treesCDT {
    tree * firstTreeByDiameter;   // trees in descending order by average species diameter
} treesCDT;

typedef struct treesCDT * treesADT;

treesADT newTree() {
    treesADT tree;
    if((tree = calloc(1, sizeof(treesCDT))) == NULL) {
        printf("No memory available\n");
        return no_mem;
    }
    return tree;
}

<<<<<<< HEAD
void freeTree
static Neighborhood *addRecHood(Neighborhood first, )
void addHood(Neighborhood hood, treesADT tree)
{

    Neighborhood *aux=NULL;// an auxiliary pointer to node is created to save the newly created node's memory location
    tree->treeQtyFirst=addRec(tree->treeQtyFirst,hood, &aux);
}
=======

>>>>>>> 1d4453e778f06029cffa42f2562d6c5d5bdc8417


