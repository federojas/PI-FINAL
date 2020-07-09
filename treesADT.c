#include "treesADT.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define BLOCK 100

typedef struct tTree {
    char * common_name;             // scientific name
    float diameterSum;              // sum of all database species diameters
    size_t qty;                     //amount of species specimens on data base
    float diameterMean;             // average diameter of tree species
} tTree;

typedef struct treeNode {
    tTree tree;
    struct treeNode * tail;
} treeNode;

typedef struct treesCDT {
    treeNode * firstTree;               // trees in descending order by average species diameter, alphabetical order used to resolve draws
    tTree * treeVect;                   // Vector containing all of the tree species in the data base
    size_t vectSize;                    // amount of species in vector
    size_t vectDim;                     // amount of space in vector
} treesCDT;

typedef struct treesCDT * treesADT;

int addTree (treesADT tree, char * name, size_t diameter)
{ 
    for(int i = 0; i < tree->vectSize; i++)
    {
        if(strcmp(tree->treeVect[i].common_name, name) == 0)
        {
            tree->treeVect[i].qty += 1;
            tree->treeVect[i].diameterSum += diameter;
            return OK;
        }
    }
    if (tree->vectDim % BLOCK == 0) 
    {
        tree->vectDim += BLOCK;
        tree->treeVect = realloc(tree->treeVect, tree->vectDim * sizeof(tTree));
        if (tree->treeVect == NULL) {
            return NO_MEM;
        }
    }
    tree->treeVect[tree->vectSize].common_name = realloc(tree->treeVect[tree->vectSize].common_name, (strlen(name)+1)*sizeof(char));
    if(tree->treeVect[tree->vectSize].common_name == NULL) {
        return NO_MEM;        
    }
    strcpy(tree->treeVect[tree->vectSize].common_name, name);
    tree->treeVect[tree->vectSize].diameterSum = diameter;
    tree->treeVect[tree->vectSize].qty = 1;
    tree->vectSize += 1;
    return OK;
}

void diamAvg(treesADT tree) // calculates all of the species average diameters
{
    float diameter;
    size_t quantity;
    for(int i = 0; i < tree->vectSize; i++) {
        diameter = tree->treeVect[i].diameterSum;
        quantity = tree->treeVect[i].qty;
        tree->treeVect[i].diameterMean = (float)(diameter/quantity);
    }
}

static treeNode * addRecTree (treeNode * first, tTree tree) {
    if (first == NULL || first->tree.diameterMean < tree.diameterMean) {
            treeNode * aux = malloc(sizeof(treeNode));
        if (aux == NULL) {
            return NULL;        
        }
        aux->tree.common_name = realloc(aux->tree.common_name, strlen(tree.common_name)+1);
        if (aux->tree.common_name == NULL)
            return NULL;
        strcpy(aux->tree.common_name, tree.common_name);
        aux->tail = first;
        return aux;
    }
    if (first->tree.diameterMean == tree.diameterMean) {
        if (strcmp(first->tree.common_name, tree.common_name) > 0) {
            treeNode * aux = malloc(sizeof(treeNode));
            if (aux == NULL) {
                return NULL;        
            }
            aux->tree.common_name = realloc(aux->tree.common_name, strlen(tree.common_name)+1);
            if (aux->tree.common_name == NULL)
                return NULL;
            strcpy(aux->tree.common_name, tree.common_name);

            aux->tail = first;
            return aux;
        }
    }
    first->tail = addRecTree(first->tail, tree);
    return first;
}

int treeList (treesADT tree) {
    tree->treeVect = realloc(tree->treeVect, tree->vectSize * sizeof(tTree)); // we free up unused memory
    if(tree->treeVect == NULL) {
        printf("No memory available\n");
        return NO_MEM;        
    }
    for(int i = 0; i < tree->vectSize; i++) {
        tree->firstTree = addRecTree(tree->firstTree, tree->treeVect[i]);
        if (tree->firstTree == NULL) {
            return NO_MEM;
        }
        free(tree->treeVect[i].common_name);
    }
    free(tree->treeVect);
    tree->treeVect = NULL;
    return OK;
}

treesADT newTree() {
    treesADT tree = calloc(1, sizeof(treesCDT));
    if(tree == NULL) return NULL;
    return tree;
}

int main(int argc, char const *argv[]){
    FILE *trees;
    trees=fopen(argv[1],"r");
    char lines[10000];
    fgets(lines,10000, trees);
    //me fijo en donde esta la columna con nombre de arboles 
    char *token;
    token=strtok(lines,"; ");
    int countNombre =0,countDiametro=0,nombre=0,diametro=0,salir=0;
    while(token!=NULL && !salir){
        if(strcmp("nombre_cientifico",token)==0)
        {
            nombre=1;
        }
        if(strcmp("diametro_altura_pecho",token)==0){
            diametro==1;
        }
            if(nombre==0)
                countNombre++;
            if(diametro==0)
                countDiametro++;
            if(diametro!=0 && nombre!=0)
                salir=1;
        token=strtok(NULL,"; ");

    }
    printf("%d\n",countDiametro);
    //ahora tengo el contador por lo que tengo que guardarme esa key 
    int i,j;
    char name[100];
    while(fgets(lines, 10000, trees))
    {
        i=0,j=0;
        token=strtok(lines,";");
        while(token!=NULL){
            if(i==countNombre)
            {
                strcpy(name,token);
               // printf("%s\n",name);

            }
            if(j==11)
            {
                diametro=atoi(token);
                printf("%d\n",diametro);

            }
            i++;
            j++;
            token=strtok(NULL,";");

        }
        printf("%s\t%d\n",name,diametro);

    }

}