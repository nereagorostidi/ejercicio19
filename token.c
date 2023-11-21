#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char **split (char *s, char *delimiter, int *cap, int *error){

    char **array;
    *error=0;
    errno=0;
    char *token;
    int numveces=0;
    array = (char**) malloc(sizeof(char*));

    *cap = 1;
    if(array==NULL){
        *error=errno;
        return NULL;
    }

    if(s==NULL||delimiter==NULL){
        array[numveces]=NULL;
        return array;
    }

    token=strtok(s, delimiter);
    while(token!=NULL){

        array[numveces]= strdup(token);

        if(array[numveces]==NULL){
            *error=errno;
            return NULL;
        }
        printf("Numero de veces %d, token %s, cap %d\n", numveces, token, *cap); 
        numveces++;

        if(*cap<=numveces){
          
            //array=(char**) realloc(array, 2*sizeof(array));
             array=(char **) realloc(array, (*cap) * 2* sizeof(char *));
             *cap=(*cap)*2;
             if(array==NULL){
                *error=errno;
                return NULL;
             }
        }
        token=strtok(NULL, delimiter);
    }

    array[numveces]=NULL;
    return array;

}

void freesplit(char **array, int cap){
    
    if(cap==0){
        free(array);
        return;
    }
    
    for(int x=0; x<cap-1; x++){
        free(array[x]);
    }

    free(array);
    return;
}

