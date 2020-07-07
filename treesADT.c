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