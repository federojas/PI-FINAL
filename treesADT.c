#include "treesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct tTree {
    char * common_name; // scientific name
    size_t diameterSum; // sum of all database species diameters
    size_t qty; //amount of species specimens on data base
    size_t diameterMean; // average diameter of tree species
} tTree;

typedef struct tree {
    tTree tree;
    struct tree * tail;
} tree;

typedef struct treesCDT {
    tree * firstTree;   // trees in descending order by average species diameter, alphabetical order used to resolve draws
} treesCDT;

typedef struct treesCDT * treesADT;

treesADT newTree() {
    treesADT tree;
    if((tree = calloc(1, sizeof(treesCDT))) == NULL) {
        printf("No memory available\n");
    }
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

