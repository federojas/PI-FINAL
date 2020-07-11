#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#define OK 1
#define NO_MEM 0
#define BLOCK 100
#define MAX_BUFFER 1024

typedef struct tTree {
    char * common_name;                 // scientific name
    char * hood_name;
    float diameterSum;                  // sum of all database species diameters
    long unsigned int qty;              // amount of species specimens on data base
    float diameterMean;                 // average diameter of tree species
} tTree;

typedef struct treeNode {
    char * common_name; 
    float diameterMean;  
    struct treeNode * tail;
} treeNode;

typedef struct tHood {
    char * hood_name;
    size_t treeQty;
    size_t habitants;
    float treesPerHab;
} tHood;

typedef struct hoodNode {
    char * hood_name;
    size_t treeQty;
    float treesPerHab;
    struct hood * tail;
} hoodNode;

typedef struct forestControlCDT {
    treeNode * firstTree;
    tTree * treeVector;
    size_t treeSize;
    tHood * firstHoodByQty;
    tHood * firstHoodByTPP;
    tHood * hoodVector;
    size_t hoodSize;
} forestControlCDT;

typedef struct forestControlCDT * forestControlADT;

forestControlADT newForestControl() {
    return calloc(1, sizeof(forestControlADT));
}

/*void freeRec (treeNode * first) {
    if (first == NULL)
        return ;
    freeRec (first->tail);
    free(first->common_name);
    free(first);
}

void freeTree (forestControlADT tree) {
    freeRec(tree->firstTree);
    // reminder: cada elemento del vector es eliminado cuando se pasa a la lista
    free(tree);
}*/

void addTree (forestControlADT fc, const char * commonName, const char * hoodName, const float diameter) {
    int salir1 = 0;
    for (size_t i = 0; i < fc->treeSize && !salir1; i++) {
        if (strcmp(fc->treeVector[i].common_name, commonName) == 0) {
            fc->treeVector[i].diameterSum += diameter;
            fc->treeVector[i].qty++;
            salir1 = 1;
        }
    }
    
    int salir2 = 0;
    for (size_t i = 0; i < fc->hoodSize && !salir2; i++) {
        if (strcmp(fc->hoodVector[i].hood_name, hoodName) == 0) {
            fc->hoodVector[i].treeQty++;
            salir2 = 1;
        }
    }
    
    if (salir1 && salir2)
        return ;
    
    if (fc->treeSize % BLOCK == 0) {
        fc->treeVector = realloc(fc->treeVector, (fc->treeSize + BLOCK) * sizeof(tTree));
    }
    if (fc->hoodSize % BLOCK == 0) {
        fc->hoodVector = realloc(fc->hoodVector, (fc->hoodSize + BLOCK) * sizeof(tHood));
    }
    
    fc->treeVector[fc->treeSize].common_name = realloc(fc->treeVector[fc->treeSize].common_name, strlen(commonName)+1);
    strcpy(fc->treeVector[fc->treeSize].common_name, commonName);
    fc->treeVector[fc->treeSize].diameterSum = diameter;
    fc->treeVector[fc->treeSize].qty = 1;
    fc->treeSize++;
    
    fc->hoodVector[fc->hoodSize].hood_name = realloc(fc->hoodVector[fc->hoodSize].hood_name, strlen(hoodName)+1);
    strcpy(fc->hoodVector[fc->hoodSize].hood_name, hoodName);
    fc->hoodVector[fc->hoodSize].habitants = 0;
    fc->hoodVector[fc->hoodSize].treeQty = 1;
    fc->hoodSize++;
}

void diamAvg (forestControlADT fc) {
// calculates all of the species average diameters
    float diameter;
    long unsigned int quantity;
    for (int i = 0; i < fc->treeSize; i++) {
        diameter = fc->treeVector[i].diameterSum;
        quantity = fc->treeVector[i].qty;
        fc->treeVector[i].diameterMean = (float)(diameter/quantity);
    }
}

// hay que cambiar el compare este
static float compare1 (size_t diamMean1, size_t diamMean2) {
    return diamMean1 - diamMean2;
}

static treeNode * addTreeRec (treeNode * first, tTree tree) {
    int c;
    if (first == NULL || (c = compare1(first->diameterMean, tree.diameterMean)) < 0) {
        treeNode * aux = malloc(sizeof(treeNode));
        aux->common_name = malloc(sizeof(char)*(strlen(tree.common_name)+1));
        aux->diameterMean = tree.diameterMean;
        strcpy(aux->common_name,tree.common_name);    
        aux->tail = first;
        return aux;
    }
    if (c == 0) {
        if (strcmp(first->common_name, tree.common_name) > 0) {
            treeNode * aux = malloc(sizeof(treeNode));
            aux->common_name = malloc(sizeof(char) * (strlen(tree.common_name)+1));
            aux->diameterMean = tree.diameterMean;
            strcpy(aux->common_name, tree.common_name);
            aux->tail = first;
            return aux;
        }
    }
    first->tail = addTreeRec(first->tail, tree);
    return first;
}

void treeToTreeList (forestControlADT fc, tTree source) {
    fc->firstTree = addTreeRec(fc->firstTree, source);
}
// faltaria ver donde reallocamos la memoria del vector con el size
void treeVecToTreeList (forestControlADT fc) {
    diamAvg(fc); // we calculate the diameter average of each species
    for (size_t i = 0; i < fc->treeSize; i++) {
        treeToTreeList(fc, fc->treeVector[i]);
        //free(fc->treeVector[i]);
        //free(fc->treeVector[i].common_name);
    }
    //free(fc->treeVector);
    return ;
}

static int compare2 (size_t treeQty1, size_t treeQty2) {
    return treeQty1 - treeQty2;
}
// pa mi queda mejor el struct con tHood y tTree
static hoodNode * addHoodByQtyRec (hoodNode * first, tHood hood) {
    int c;
    if (first == NULL || (c = compare2(first->treeQty, hood.treeQty)) < 0) {
        hoodNode * aux = malloc(sizeof(hoodNode));
        aux->hood_name = malloc(sizeof(char) * (strlen(hood.hood_name)+1));
        strcpy(aux->hood_name, hood.hood_name);
        aux->treeQty = hood.treeQty;
        aux->treesPerHab = 0; // o algun valor que diga que no importa en esta lista
        aux->tail = first;
        return aux;
    }
    if (c == 0) {
        if (strcmp(first->hood_name, hood.hood_name) > 0) {
            hoodNode * aux = malloc(sizeof(hoodNode));
            aux->hood_name = malloc(sizeof(char) * (strlen(hood.hood_name)+1));
            strcpy(aux->hood_name, hood.hood_name);
            aux->treeQty = hood.treeQty;
            aux->tail = first;
            return aux;
        }
    }
    first->tail = addHoodByQtyRec(first->tail, hood);
    return first;
}

void hoodToHoodListByQty (forestControlADT fc, tHood source) {
    fc->firstHoodByQty = addHoodByQtyRec (fc->firstHoodByQty, source);
}

void hoodVecToHoodListByQty (forestControlADT fc) {
    for (size_t i = 0; i < fc->hoodSize; i++) {
        hoodToHoodListByQty(fc, fc->hoodVector[i]);
    }
    return ;
}

void addHood (forestControlADT fc, const char * hoodName, size_t habitants) {
    for (size_t i = 0; i < fc->hoodSize; i++) {
        if (strcmp(fc->hoodVector[i].hood_name, hoodName) == 0) {
            fc->hoodVector[i].habitants += habitants;
        }
    }
}
// en caso de que algun barrio pasado de los arboles.csv no este en barrios.csv, tomamos que su poblacion es cero

void treesPerHab (forestControlADT fc) {
    
    size_t habs;
    size_t treeQty;
    for (int i = 0; i < fc->hoodSize; i++) {
        habs = fc->hoodVector[i].habitants;
        treeQty = fc->hoodVector[i].treeQty;
        fc->hoodVector[i].treesPerHab = (float)(treeQty/habs);
    }
}
static int compare3 (size_t tpp1, size_t tpp2) {
    return tpp1 - tpp2;
}
// pa mi queda mejor el struct con tHood y tTree
static hoodNode * addHoodByTPP (hoodNode * first, tHood hood) {
    int c;
    if (first == NULL || (c = compare3(first->treesPerHab, hood.treesPerHab)) < 0) {
        hoodNode * aux = malloc(sizeof(hoodNode));
        aux->hood_name = malloc(sizeof(char) * (strlen(hood.hood_name)+1));
        strcpy(aux->hood_name, hood.hood_name);
        aux->treeQty = hood.treeQty;
        aux->treesPerHab = hood.treesPerHab;
        aux->tail = first;
        return aux;
    }
    if (c == 0) {
        if (strcmp(first->hood_name, hood.hood_name) > 0) {
            hoodNode * aux = malloc(sizeof(hoodNode));
            aux->hood_name = malloc(sizeof(char) * (strlen(hood.hood_name)+1));
            strcpy(aux->hood_name, hood.hood_name);
            aux->treeQty = hood.treeQty;
            aux->treesPerHab = hood.treesPerHab;
            aux->tail = first;
            return aux;
        }
    }
    first->tail = addHoodByTPP(first->tail, hood);
    return first;
}

void hoodToHoodListByTPP (forestControlADT fc, tHood source) {
    fc->firstHoodByTPP = addHoodByTPP (fc->firstHoodByTPP, source);
}

void hoodVecToHoodListByTPP (forestControlADT fc) {
    for (size_t i = 0; i < fc->hoodSize; i++) 
        hoodToHoodListByTPP(fc, fc->hoodVector[i]);
    return ;
}
    
static void printTreeList (forestControlADT fc){
    treeNode * aux = fc->firstTree;
    while (aux != NULL) {
        printf("%s\t%.2f\n", aux->common_name, aux->diameterMean);
        aux = aux->tail;
    }
}


int main(int argc, char const *argv[]) {
    FILE * trees;
    char * token;
    trees = fopen(argv[1],"r");
    char lines[MAX_BUFFER];
    char name[30], hood[30];
    fgets(lines,1024, trees);
    int i,registro;
    float diametro;
    forestControlADT fc = newForestControl();
    
    while(fgets(lines, MAX_BUFFER, trees)) {
        for(i=0,token=strtok(lines,";");i<12;i++)
        {
            if(i==2)
            {
                strcpy(hood,token);
            }
            if(i==7)
            {
                strcpy(name,token);
            }
            if(i==11) {
                diametro = atof(token);
            }
            token=strtok(NULL,";");
        }
        if(diametro != 0)
            addTree(fc, name, hood, diametro);
    }
    treeVecToTreeList(fc);
    printTreeList(fc);
}
