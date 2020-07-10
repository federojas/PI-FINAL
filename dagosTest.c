#include "treesADT.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#define OK 1
#define NO_MEM 0
#define BLOCK 100

typedef struct tTree {
    char * common_name;             // scientific name
    float diameterSum;              // sum of all database species diameters
    long unsigned int qty;                     //amount of species specimens on data base
} tTree;

typedef struct treeNode {
    tTree tree;
    struct treeNode * tail;
} treeNode;

typedef struct treesCDT {
    tTree * vec;                   // Vector containing all of the tree species in the data base
    size_t size;                    // amount of species in vector
} treesCDT;

typedef struct treesCDT * treesADT;

treesADT newTree () {
    return calloc(1, sizeof(treesCDT));
}

int dbToVector (treesADT tree, const char * name, const float diameter) {
    for (int i = 0; i < tree->size; i++) {
        if (strcmp(tree->vec[i].common_name, name) == 0) {
            tree->vec[i].diameterSum += diameter;
            tree->vec[i].qty++;
            return 1;
        }
    }
    
    if (tree->size % BLOCK == 0) {
        tree->vec = realloc(tree->vec, (tree->size + BLOCK) * sizeof(tTree));
    }
    
    tree->vec[tree->size].common_name = realloc(tree->vec[tree->size].common_name, strlen(name)+1);
    strcpy(tree->vec[tree->size].common_name, name);
    tree->vec[tree->size].diameterSum = diameter;
    tree->vec[tree->size].qty = 1;
    tree->size++;
    return 1;
}

int criterio (const void *p, const void *q) {
    float avgt1 = ((tTree *)p)->diameterSum / ((tTree *)p)->qty;
    float avgt2 = ((tTree *)q)->diameterSum / ((tTree *)q)->qty;
    return avgt2 - avgt1;
}
 
void printVector (const tTree * vec, size_t dim) {
    for (size_t i = 0; i < dim; i++) {
        printf("%s;", vec[i].common_name);
        printf("%.02f\n", vec[i].diameterSum/vec[i].qty);
    }
}

int main (int argc, char const *argv[]){
    FILE *trees;
    trees=fopen(argv[1],"r");
    char lines[10000];
    fgets(lines,10000, trees);
    //me fijo en donde esta la columna con nombre de arboles 
    char *token;
    token=strtok(lines,"; ");
    int countNombre =0,countDiametro=0,nombre=0,diametro=0,salir=0;
    treesADT tree = newTree();
    //este while lo uso para saber que columnas son las que uso pero no se si hacen falta pq ya abriendo el archivo se cuales son 
    while (token != NULL && !salir) {
        if (strcmp("nombre_cientifico",token) == 0)
            nombre=1;
        if (strcmp("diametro_altura_pecho",token) == 0)
            diametro = 1;
        if (nombre == 0)
            countNombre++;
        if (diametro == 0)
            countDiametro++;
        if (diametro != 0 && nombre != 0)
            salir=1;
        token=strtok(NULL, "; ");
    }
    printf("%d\n", countDiametro);
    //ahora tengo el contador por lxo que tengo que guardarme esa key 
    int i,j;
    char name[100];
    while(fgets(lines, 10000, trees)) {
        i=0,j=0;
        token=strtok(lines,";");
        while(token!=NULL){
            if(i==countNombre) {
                strcpy(name,token);
               // printf("%s\n",name);
            }
            if(j==11){
                diametro=atoi(token);
                //printf("%d\n",diametro);
            }
            i++;
            j++;
            token=strtok(NULL,";");
        }
        dbToVector(tree, name, diametro);
    }
    qsort(tree->vec, tree->size, sizeof(tTree), criterio);
    printVector(tree->vec, tree->size);
}