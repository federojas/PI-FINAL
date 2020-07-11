#ifndef hoodADT_h
#define hoodADT_h
typedef hoodCDT * hoodADT; //esto va en el .h ¿?
hoodADT newHood();
int addHood (hoodADT hood, char * name, size_t habitants);
int addTreeHood(hoodADT hood, char * treeHood);
void freeHood(hoodADT hood);
int hoodList (hoodADT hood);
#endif