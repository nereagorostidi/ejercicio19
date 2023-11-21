#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {


    //char *meses = "enero,febrero,marzo,junio,julio";
    char meses[] = "enero,febrero,marzo,junio,julio,agosto";

    printf("los meses son %s\n", meses);

    char **mes = (char **)malloc(5 * sizeof(char *));
/*
    mes[0] = strtok(meses, ",");
    mes[1] = strtok(NULL, ",");
    mes[2] = strtok(NULL, ",");
    mes[3] = strtok(NULL, ",");
    mes[4] = strtok(NULL, ",");*/

    // Tokenize the string and populate the mes array using a loop
    int i = 0;
    char *token = strtok(meses, ",");
    while (token != NULL) {
        mes[i] = token;
        token = strtok(NULL, ",");
        i++;
    }
    mes[i]=NULL;


    for (int x = 0; x < i; x++) {
        printf("mes %d, %s\n", x, mes[x]);
    }

    // Don't forget to free the allocated memory
    free(mes);
    
    return 0;
}

