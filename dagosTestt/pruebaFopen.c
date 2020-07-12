#include <stdio.h>
int main(){
    FILE *preg1;
    FILE *preg2, *preg3;
    char asd[]="hola";
    //char asd2[]="como estas";
    preg3= fopen("preg3.csv","w");
    preg2=fopen("preg1.csv","w");
    preg1=fopen("preg2.csv","w");
    fprintf(preg1,"%s\n",asd);
    
    // fprintf(preg2,"%s\n",asd2);
}