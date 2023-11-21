#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "token.h"
int main (int argc, char* argv[]){

    char *cadena;
    cadena=strdup("Soy nerea Gorostidi");
    printf("%s\n", cadena);
    char *d;
    d=strdup(" ");
    char **palabras;
    int t=0;
    int error=0;
    palabras= split(cadena,d,&t,&error);
    freesplit(palabras,t);
 }
