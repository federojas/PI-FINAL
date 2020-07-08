#include "hoodADT.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct tHood {
    char * hood_name;
    size_t habitants;
    size_t treeQty;
    size_t treesPerHab;
} tHood;

typedef struct hood {
    tHood hood;
    struct hood * tail;
} hood;

typedef struct hoodCDT {
    hood * firstHoodQty;          // neighborhoos in descending order by qty
    hood * firstHoodHab;          // neighborhoos in descending order by qty/habitants
}