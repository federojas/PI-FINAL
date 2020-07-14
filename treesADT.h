#include <stddef.h>
#ifndef treesADT_h
#define treesADT_h

typedef struct treesCDT * treesADT; 

//creates a new treeADT
treesADT newTree();

//frees up all used memory
void freeTree (treesADT tree);

//adds a tree to the tree vector
int addTree (treesADT tree, const char * name, const double diameter);

//creates a list in descending order of tree species diameter average. Alphabetical order used as secondary sorting criteria.
void treeList (treesADT tree);

//sets the current iterator to the beginning of the list
void toBegin(treesADT tree);

//checks if the current iterator is at the end of the list
int hasNext(treesADT tree);

//advances the current iterator to the next node
double next(treesADT tree, char *name );

#endif