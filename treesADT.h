#include <stddef.h>
#ifndef treesADT_h
#define treesADT_h
typedef struct treesCDT * treesADT; 
typedef struct tTree {
    char * common_name;                 // scientific name
    float diameterSum;                  // sum of all database species diameters
    long unsigned int qty;              // amount of species specimens on data base
    float diameterMean;                 // average diameter of tree species
} tTree;
treesADT newTree();
//function that returns the amount of hoods sabed
int hoodAmount(treesADT tree);
void freeTree (treesADT tree);
int addTree (treesADT tree, const char * name, const float diameter);
void elemToList (treesADT tree, tTree source);
void vecToList (treesADT tree);
void printList (treesADT tree); //esta capaz la saque desps

#endif