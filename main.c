#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "token.h"
#include <signal.h>

char* buffer;          //lo declaro global para poder liberrlo a traves de la funcion libero

void mysignalhandler(){
    printf("Adios");
    exit(EXIT_SUCCESS);
}

void liberar(){
    printf("Ejecutando liberar");
    free(buffer);
}
int main (int argc, char* argv[]){

    //TESTEO PROBAR FUNCIONES 

    /*char *cadena;
    cadena=strdup("Soy nerea Gorostidi");
    printf("%s\n", cadena);
    palabras= split(cadena,d,&t,&error);
    char *d;
    d=strdup(" ");
    char **palabras;
    int t=0;
    int error=0;
    freesplit(palabras,t);*/

    size_t  n;
    char *d;
    d=strdup(" ");
    char **palabras;
    int t=0;
    int error=0;
    pid_t pid_dead;
    int status;

    atexit(liberar);

    signal(SIGINT, &mysignalhandler);
    printf("Shell menu. Introduce a command, EXIT or CTRL+C for exit.\n");
    while(getline(&buffer, &n, stdin)!=-1){
       
        int l= strlen(buffer);
        buffer[l-1]=0;

        printf("my_shell: %s\n", buffer);
        if(strcmp(buffer, "EXIT")==0){
            exit(EXIT_SUCCESS);
        }

        if(strcmp(buffer, "")){ // Si he escrito algo

            int fd[2];
            pipe(fd);
            int pid=fork();
            
            if(pid==0){ // Ejecuto comando shell
                close(1);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                palabras= split(buffer,d,&t,&error);
                execvp(palabras[0], palabras);
                perror("No existe ese comando");
                exit(EXIT_SUCCESS);

            } // Fin de hijo

            else{ // Comienzo Padre
                close(fd[1]);       //cerramos extremo escritura del pipe 
                int num_bytes;
                char readbuffer[2048];
                char *salida="Output";
                while((num_bytes=read(fd[0], readbuffer, sizeof(readbuffer)))>0){
                    printf("%s\n", salida);
                    write(STDOUT_FILENO, readbuffer, num_bytes);
                    //printf("%s\n", readbuffer);
               
                } // Fin del while del read buffer 
                
                close(fd[0]);       //cerramos extremo lectura del pipe 
              //  exit(EXIT_SUCCESS);

            } // Fin del padre

            pid_dead=wait(&status);
            printf("My son %i died with status %d\n", pid_dead, WEXITSTATUS(status)); 

           } // Fin de comparacion de si he escrito algo en en shell

     } // Fin de While del getline (de lectura de comandos desde el stdin))

  exit(EXIT_SUCCESS);
 }


