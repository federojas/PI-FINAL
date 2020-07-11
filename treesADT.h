#ifndef treesADT_h
#define treesADT_h
typedef struct treesCDT * treesADT; //esto va en el .h ¿?
treesADT newTree();
//function that returns the amount of hoods sabed
int hoodAmount(treesADT tree);
void freeTree (treesADT tree);
int addTree (treesADT tree, const char * name, const float diameter);
void elemToList (treesADT tree, tTree source);
void vecToList (treesADT tree);
#endif