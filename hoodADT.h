#include <stddef.h>

#ifndef hoodADT_h
#define hoodADT_h

typedef struct hoodCDT * hoodADT; 
hoodADT newHood();
int addHood (hoodADT hood, char * name, size_t habitants);
int addTreeHood(hoodADT hood, char * treeHood);
void freeHood(hoodADT hood);
int hoodList (hoodADT hood);
#endif