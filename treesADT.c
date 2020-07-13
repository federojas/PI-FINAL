#include "treesADT.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

#define BLOCK 100
#define OK 1

typedef struct treeNode {
    char * common_name; 
    double diameterMean;  
    struct treeNode * tail;
} treeNode;

typedef struct
{
    char * common_name; //scientific name
    double diameterSum; //sum of species specimen diameters in database
    long unsigned int qty; //amont of species specimnes in database
    double diameterMean; //average diameter of tree species
}tTree;

typedef struct treesCDT {
    treeNode * firstTree;               // trees in descending order by average species diameter, alphabetical order used to resolve draws
    treeNode *current;
    tTree * vector;                     // Vector containing all of the tree species in the data base
    size_t size;                        // amount of species in vector
} treesCDT;

treesADT newTree() {
    treesADT tree;
    tree = calloc(1, sizeof(treesCDT));
    if(errno == ENOMEM)
    {
        perror("Error");
        return NULL;
    }
    return tree;
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
    free(tree);
}

int addTree (treesADT tree, const char * name, const double diameter) {
    for (int i = 0; i < tree->size; i++) {
        if (strcmp(tree->vector[i].common_name, name) == 0) {
            tree->vector[i].diameterSum += diameter;
            tree->vector[i].qty++;
            return OK;
        }
    }
    
    if (tree->size % BLOCK == 0) {
        tree->vector = realloc(tree->vector, (tree->size + BLOCK) * sizeof(tTree));
        if(errno == ENOMEM)
            {
                perror("Error");
                return ENOMEM;
            }
    }
    tree->vector[tree->size].common_name = malloc((strlen(name)+1)*sizeof(char));
    if(errno == ENOMEM)
    {
        perror("Error");
        return ENOMEM;
    }
    strcpy(tree->vector[tree->size].common_name, name);
    tree->vector[tree->size].diameterSum = diameter;
    tree->vector[tree->size].qty = 1;
    tree->size++;
    return OK;
}

static void diamAvg (treesADT tree) // calculates all of the species average diameters
{
    double diameter;
    long unsigned int quantity;
    for (int i = 0; i < tree->size; i++) {
        diameter = tree->vector[i].diameterSum;
        quantity = tree->vector[i].qty;
        double diameterAvg = floorf( (diameter/(double)quantity) * 100) / 100;
        tree->vector[i].diameterMean = diameterAvg;
    }
}

static treeNode * addRecTree (treeNode * first, tTree tree) {
    if (first == NULL || first->diameterMean < tree.diameterMean) {
        treeNode * aux = malloc(sizeof(treeNode));
        if(errno == ENOMEM)
        {
            perror("Error");
            return NULL;
         }
        aux->common_name = malloc((strlen(tree.common_name)+1)*sizeof(char));
         if(errno == ENOMEM)
         {
            perror("Error");
            return NULL;
         }
        aux->diameterMean = tree.diameterMean;
        strcpy(aux->common_name,tree.common_name);    
        aux->tail = first;
        return aux;
    }
    if (first->diameterMean == tree.diameterMean) {
        if (strcmp(first->common_name, tree.common_name) > 0) {
            treeNode * aux = malloc(sizeof(treeNode));
            if(errno == ENOMEM)
            {
                perror("Error");
                return NULL;
            }
            aux->common_name = malloc((strlen(tree.common_name)+1)*sizeof(char));
            if(errno == ENOMEM)
            {
                perror("Error");
                return NULL;
            }
            aux->diameterMean=tree.diameterMean;
            strcpy(aux->common_name, tree.common_name);
            aux->tail = first;
            return aux;
        }
    }
    first->tail = addRecTree(first->tail, tree);
    return first;
}


void vecToList (treesADT tree) {
    diamAvg(tree); // we calculate the diameter average of each species
    for (size_t i = 0; i < tree->size; i++) {
        tree->firstTree = addRecTree(tree->firstTree, tree->vector[i]);
        free(tree->vector[i].common_name);
    }
    free(tree->vector);
    return ;
}


void toBegin(treesADT tree){
    tree->current=tree->firstTree;
}
int hasNext(treesADT tree){
    return tree->current != NULL;
} 

double next(treesADT tree, char *name )
{
    double  diameter;
    if(hasNext(tree) == 0)
        return 0;
    diameter=tree->current->diameterMean;
    strcpy(name,tree->current->common_name);
    tree->current = tree->current->tail;
    return diameter;
}

