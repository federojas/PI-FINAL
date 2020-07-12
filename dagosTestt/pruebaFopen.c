#include <stdio.h>
int main(){
    FILE *preg1,*preg2;
    char asd[]="hola",asd2[]="como estas";
    
    fopen("preg1.csv","w");
    fprintf(preg1,"%s\n",asd);
    
    // fopen("preg2.csv","w");
    // fprintf(preg2,"%s\n",asd2);
}