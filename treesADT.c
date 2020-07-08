#include "treesADT.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct tHood {
    char * hood_name;
    size_t habitants;
} tHood;

typedef struct tTree {
    char * common_name; // scientific name
    size_t diameter;
    size_t qty;
} tTree;

typedef struct hood {
    tHood hood;
    struct hood * tail;
} hood;

typedef struct tree {
    tTree tree;
    struct tree * tail;
} tree;

typedef struct treesCDT {
    hood * firstHood1;          // tomando con orden qty
    hood * firstHood2;           // tomando con orden qty/habitants
    tree * firstTreeByDiameter;
} treesCDT;

typedef struct treesCDT * treesADT;

typedef struct node1
{
    struct node1 * treeQtyTail; // tail to next neighborhood node by order of amount of trees per neighborhood
    struct node1 * treesPerHabTail; // tail to next neighborhood node by order of amount of trees per habitant
    char * name; // neighborhood name
    size_t treeQty; // amount of trees per neighborhood
    size_t treesPerHab; // amount of trees per habitant
}Neighborhood;

typedef struct tTree {
    char * name; // scientific name
    size_t quantity; // total number of specimens used to calculate diameterMean
    size_t diameterSum; // sum of all specimen diameters used to calculate diameterMean
    size_t diameterMean; // diameter average of tree species
} tTree;

typedef struct node2 {
    tTree tree;             // specs of the current tree
    struct node2 * treeTail; // tail to next tree node
} Tree;

typedef struct 
{
    Neighborhood * treeQtyFirst; // pointer to first node in descending order by quantity of trees
    Neighborhood * treePerHabFirst; // pointer to first node in descending order by amount of trees per habitant
    Tree * treeFirst; // pointer to first node in descending order by diamater average of a tree type
}treesCDT;

typedef treesCDT * treesADT;

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

static void freeRec(Neighborhood * hood, Tree * tree)
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
static Neighborhood *addRecHood(Neighborhood first, )
void addHood(Neighborhood hood, treesADT tree)
{

    Neighborhood *aux=NULL;// an auxiliary pointer to node is created to save the newly created node's memory location
    tree->treeQtyFirst=addRec(tree->treeQtyFirst,hood, &aux);
}

static Tree * addTreeRec(Tree * tree, Tree tree)
{

}

void addTree(treesADT tree_collection, Tree tree)
{
    tree_collection->treeFirst = addTreeRec(tree_collection->treeFirst, tree);
}

