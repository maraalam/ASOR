#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char * argv[]){

    if(argc < 2){
        perror("Numero incorrecto de parametros\n");
        exit(1);
    }

    pid_t pid = fork();


    if(pid == -1){
        perror("fork");
        exit(1);
    }
    else if(pid == 0){ //Hijo
        pid_t sid = setsid();
        char *new_dir = chdir("/tmp");

        printf("Atributos del proceso hijo\n");
        printf("PID: %d\n",getpid());
        printf("PPID: %d\n",getppid());
        printf("PGID: %d\n", getpgid(getpid()));
        printf("SID %d\n", sid);

        execvp(argv[1],argv+1);
    }
    else{ // Padre
        wait(NULL);
    }


}