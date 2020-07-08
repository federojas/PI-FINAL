#include "hoodADT.h"
#include <stdio.h>
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
    hood * firstHoodQty;          // neighborhoods in descending order by qty, alphabetical order used to resolve draws
    hood * firstHoodHab;          // neighborhoods in descending order by qty/habitants, alphabetical order used to resolve draws
}

typedef hoodCDT * hoodADT;

hoodADT newHood() {
    hoodADT hood;
    if((hood = calloc(1, sizeof(hoodCDT))) == NULL) {
        printf("No memory available\n");
        return NO_MEM;
    }
    return hood;
}
