#include "treesADT.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct tHood {
    char * hood_name;
    size_t habitants;
    size_t treeQty;
     size_t treesPerHab;
} tHood;

typedef struct tTree {
    char * common_name; // scientific name
    size_t diameter;
    size_t qty;
    size_t diameterMean; // average diameter of tree species
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
    hood * firstHoodQty;          // neighborhoos in descending order by qty
    hood * firstHoodHab;          // neighborhoos in descending order by qty/habitants
    tree * firstTreeByDiameter;   // trees in descending order by average species diameter
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




