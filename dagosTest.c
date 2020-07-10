/*#include "treesADT.h"
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
    treeNode * firstTreeNode;
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

static treeNode * addRec (treeNode * first, tTree source) {

}

int elemToList (treesADT tree, tTree source) {
    tree->firstTreeNode = addRec(tree->firstTreeNode, source);
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
    
}*/

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
    treeNode * firstTreeNode;
    tTree * vec;                   // Vector containing all of the tree species in the data base
    size_t size;                    // amount of species in vector
} treesCDT;

typedef struct treesCDT * treesADT;

static double compare (tTree tree1, tTree tree2) {
    return tree1.diameterSum/tree1.qty - tree2.diameterSum/tree2.qty;
}

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

static treeNode * addElemRec (treeNode * first, tTree source) {
    double c;
    if (first == NULL || (c = compare(first->tree, source)) < 0) {
        treeNode * aux = malloc(sizeof(treeNode));
        aux->tree = source;
        aux->tree.common_name = realloc(aux->tree.common_name, strlen(source.common_name)+1);
        strcpy(aux->tree.common_name, source.common_name);
        aux->tail = first;
        return aux;
    }
    if (c == 0) {
        if (strcmp(first->tree.common_name, source.common_name) > 0) {
            treeNode * aux = malloc(sizeof(treeNode));
            aux->tree = source;
            aux->tree.common_name = realloc(aux->tree.common_name, strlen(source.common_name)+1);
            strcpy(aux->tree.common_name, source.common_name);
            aux->tail = first;
            return aux;
        }
    }
    first->tail = addElemRec(first->tail, source);
    return first;
}

void elemToList (treesADT tree, tTree source) {
    tree->firstTreeNode = addElemRec(tree->firstTreeNode, source);
}

void vecToList (treesADT tree) {
    for (size_t i = 0; i < tree->size; i++)
        elemToList(tree, tree->vec[i]);
}

void printVector (const tTree * vec, size_t dim) {
    for (size_t i = 0; i < dim; i++) {
        printf("%s;", vec[i].common_name);
        printf("%.02f\n", vec[i].diameterSum/vec[i].qty);
    }
}

static void printList(treesADT tree) {
    treeNode * aux = tree->firstTreeNode;
    while (aux != NULL) {
        printf("%s;", aux->tree.common_name);
        printf("%.02f\n", aux->tree.diameterSum/aux->tree.qty);
        aux = aux->tail;
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
    vecToList(tree);
    printList(tree);
}