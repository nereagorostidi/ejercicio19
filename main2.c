#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "token.h"

char* buffer;

void mysignalhandler(){
    printf("adios\n");
    exit(EXIT_SUCCESS);
}
int main (int argc, char* argv[]){
    
    size_t n;
    while((getline(&buffer, &n, stdin))!=-1){

        int l= strlen(buffer);
        buffer[l-1]=0;
        
        printf("Has escrito: %d\n", buffer);

        if(strcmp(buffer, "EXIT")==0){
            printf("adios\n");
            exit(EXIT_SUCCESS);
        }
        
        signal(SIGINT, &mysignalhandler);
        
    }

}
