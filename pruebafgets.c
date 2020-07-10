#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char const *argv[]){
    FILE *trees;
    char *token;
    trees=fopen(argv[1],"r");
    char lines[1024];
    int i,j, registro;
    float diametro;
    char name[1024];
    fgets(lines,1024,trees);
  
    //int countNombre=0,salir=0;
//     token=strtok(lines,";");
//  while(token!=NULL && !salir){
//         if(strcmp("NEIGHBOURHOOD_NAME",token)==0)
//         {
//            salir=1;
//         }
//         countNombre++;           
//         token=strtok(NULL,";");

//     }
//     printf("%d\n",countNombre);
//     return 0 ;

    while (fgets(lines,1024,trees))
    {
        i=0;
        //token=strtok(lines,";");
        //  for (i = 0, token = strtok(line, ",\n"); i < 4; i++)
        // {
        //     if(i == 0)
        //         anio=atoi(token);
        //     if (i == 1)
        //         prov=atoi(token);
        //     if(i == 3)
        //         genero=atoi(token);
        //     token = strtok(NULL, ",\n");
        // }
        for(i=0,token=strtok(lines,";\r\t\n ");i<17;i++){
            if(token==NULL)
                i--;
            if(i==0)
            {
                registro=atoi(token);
            }
            if(i==11){
                strcpy(name,token);
            }
            if(i==15){
                diametro=atof(token);
            }
            token=strtok(NULL,";\r\t\n");
        }
        printf("%s\t%.2f\n",name,diametro);
    }   
    
}