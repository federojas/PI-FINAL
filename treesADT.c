#include "treesADT.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct tTree {
    char * common_name; // scientific name
    size_t diameterSum; // sum of all database species diameters
    size_t qty; //amount of species specimens on data base
    size_t diameterMean; // average diameter of tree species
} tTree;

typedef struct tree {
    tTree tree;
    struct tree * tail;
} tree;

typedef struct treesCDT {
    tree * firstTree;   // trees in descending order by average species diameter, alphabetical order used to resolve draws
} treesCDT;

typedef struct treesCDT * treesADT;

treesADT newTree() {
    treesADT tree;
    if((tree = calloc(1, sizeof(treesCDT))) == NULL) {
        printf("No memory available\n");
        return NO_MEM;
    }
    return tree;
}


