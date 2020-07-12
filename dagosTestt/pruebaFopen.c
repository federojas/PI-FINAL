#include <stdio.h>
int main(){
    FILE *preg1;
    FILE *preg2, *preg3;
    char asd[]="hola";
    //char asd2[]="como estas";
    fopen("preg3.csv","w");
    fopen("preg1.csv","w");
    fopen("preg2.csv","w");
    fprintf(preg1,"%s\n",asd);
    
    // fprintf(preg2,"%s\n",asd2);
}