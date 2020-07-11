#include "treesADT.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#define OK 1
#define NO_MEM 0
#define BLOCK 100

typedef struct tTree {
    char * common_name;                 // scientific name
    float diameterSum;                  // sum of all database species diameters
    long unsigned int qty;              // amount of species specimens on data base
    float diameterMean;                 // average diameter of tree species
} tTree;

typedef struct treeNode {
    char * common_name; 
    float diameterMean;  
    struct treeNode * tail;
} treeNode;

typedef struct treesCDT {
    treeNode * firstTree;               // trees in descending order by average species diameter, alphabetical order used to resolve draws
    tTree * vector;                     // Vector containing all of the tree species in the data base
    size_t size;                        // amount of species in vector
} treesCDT;

typedef struct treesCDT * treesADT; //esto va en el .h ¿?

treesADT newTree() {
    return calloc(1, sizeof(treesCDT));
}

static void freeRec (treeNode * first) {
    if (first == NULL)
        return ;
    freeRec (first->tail);
    free(first->common_name);
    free(first);
}

void freeTree (treesADT tree) {
    freeRec(tree->firstTree);
    // reminder: cada elemento del vector es eliminado cuando se pasa a la lista
    free(tree);
}

int addTree (treesADT tree, const char * name, const float diameter) {
    for (int i = 0; i < tree->size; i++) {
        if (strcmp(tree->vector[i].common_name, name) == 0) {
            tree->vector[i].diameterSum += diameter;
            tree->vector[i].qty++;
            return OK;
        }
    }
    
    if (tree->size % BLOCK == 0) {
        tree->vector = realloc(tree->vector, (tree->size + BLOCK) * sizeof(tTree));
    }
    
    tree->vector[tree->size].common_name = realloc(tree->vector[tree->size].common_name, strlen(name)+1);
    strcpy(tree->vector[tree->size].common_name, name);
    tree->vector[tree->size].diameterSum = diameter;
    tree->vector[tree->size].qty = 1;
    tree->size++;
    return OK;
}

int hoodAmount(treesADT tree){
    return tree->size;
}
static void diamAvg (treesADT tree) // calculates all of the species average diameters
{
    float diameter;
    long unsigned int quantity;
    for (int i = 0; i < tree->size; i++) {
        diameter = tree->vector[i].diameterSum;
        quantity = tree->vector[i].qty;
        tree->vector[i].diameterMean = (float)(diameter/quantity);
    }
}

static treeNode * addRecTree (treeNode * first, tTree tree) {
    if (first == NULL || first->diameterMean < tree.diameterMean) {
        treeNode * aux = malloc(sizeof(treeNode));
        aux->common_name = malloc(sizeof(char)*(strlen(tree.common_name)+1));
        aux->diameterMean = tree.diameterMean;
        strcpy(aux->common_name,tree.common_name);    
        aux->tail = first;
        return aux;
    }
    if (first->diameterMean == tree.diameterMean) {
        if (strcmp(first->common_name, tree.common_name) > 0) {
            treeNode * aux = malloc(sizeof(treeNode));
            aux->common_name = malloc(sizeof(char) * (strlen(tree.common_name)+1));
            aux->diameterMean=tree.diameterMean;
            strcpy(aux->common_name, tree.common_name);
            aux->tail = first;
            return aux;
        }
    }
    first->tail = addRecTree(first->tail, tree);
    return first;
}

void elemToList (treesADT tree, tTree source) {
    tree->firstTree = addRecTree(tree->firstTree, source);
}
// faltaria ver donde reallocamos la memoria del vector con el size
void vecToList (treesADT tree) {
    diamAvg(tree); // we calculate the diameter average of each species
    for (size_t i = 0; i < tree->size; i++) {
        elemToList(tree, tree->vector[i]);
        free(tree->vector[i]);
    }
    free(tree->vector);
    return ;
}

static void printList (treesADT tree){
    treeNode *aux=tree->firstTree;
    while (aux != NULL) {
        printf("%s\t%.2f\n",aux->common_name,aux->diameterMean);
        aux = aux->tail;
    }
}

int main(int argc, char const *argv[]){
    FILE *trees;
    char *token;
    trees = fopen(argv[1],"r");
    char lines[1024];
    char name[30],hood[5];
    fgets(lines,1024, trees);
    int i,diametro,registro;
    treesADT tree=newTree();
    while(fgets(lines,1024,trees))
    {
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
            if(i==11)
            {
                diametro=atoi(token);
            }
            token=strtok(NULL,";");
        }
        if(diametro!=0)
            addTree(tree,name,diametro);
    }
    vecToList(tree);
    printList(tree);
    freeTree(tree);
}
