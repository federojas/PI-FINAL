#include <stddef.h>

#ifndef hoodADT_h
#define hoodADT_h

typedef struct hoodCDT * hoodADT;

//creates a new hoodADT
hoodADT newHood();

//adds a neighborhood to the hood vector
int addHood (hoodADT hood, char * name, size_t habitants);

//Adds the tree to the tree quantity of its neighborhood
int addTreeHood(hoodADT hood, char * treeHood);

//frees up all used memory
void freeHood(hoodADT hood);

//creates a single neighborhood list sorted by two different criteria. Criteria 1: descending order of trees / habitant. Criteria 2: descending order of amount of trees. Both criteria use aphabetical order as a secondary sort criteria.
int vecToHoodList (hoodADT hood);

//sets the current iterator to the beginning of the list in descending order of trees / habitant
void toBeginHoodHab(hoodADT hood);

//checks if the current iterator is at the end of the list in descending order of trees / habitant
int hasNextHoodHab(hoodADT hood);

//advances the current iterator to the next node in descending order of trees / habitant
double nextHoodHab(hoodADT hood, char *hoodName);

//sets the current iterator to the beginning of the list in descending order of amount of trees
void toBeginQty(hoodADT hood);

//checks if the current iterator is at the end of the list in descending order of amount of trees
int hasNextHoodQty(hoodADT hood);

//advances the current iterator to the next node in descending order of amount of trees
void nextHoodQty(hoodADT hood, int *cant, char *hoodName);

#endif