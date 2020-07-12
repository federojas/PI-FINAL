#include <stddef.h>

#ifndef hoodADT_h
#define hoodADT_h

typedef struct hoodCDT * hoodADT; 
hoodADT newHood();
int addHood (hoodADT hood, char * name, size_t habitants);
int addTreeHood(hoodADT hood, char * treeHood);
void freeHood(hoodADT hood);
int hoodList (hoodADT hood);
void toBeginHoodHab(hoodADT hood);
int hasNextHoodHab(hoodADT hood);
double nextHoodHab(hoodADT hood, char *hoodName);
void toBeginQty(hoodADT hood);
int hasNextHoodQty(hoodADT hood);
void nextHoodQty(hoodADT hood, int *cant, char *hoodName);
#endif