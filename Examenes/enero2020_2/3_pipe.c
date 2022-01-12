#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>

#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>



int main(int argc, char *argv[]){

    if(argc < 3){
        perror("Numero incorrecto de parametros\n");
        exit(1);
    }

    char *comando1 = argv[1];
    char *comando2 = argv[2];


    int c1_c2[2];

    pipe(c1_c2);
    

    //Comando1
    pid_t pid1 = fork();
    
    if(pid1 == -1){
        perror("fork");
        exit(1);
    }
    else if(pid1 == 0){//Hijo
        close(c1_c2[0]);
        printf("Hijo 1 pid : %d\n", getpid());
        dup2(c1_c2[1],1);
        char * argvc1[]= {comando1, NULL};
        execvp(comando1, argvc1);

    }
    else{//Padre
        wait(NULL);
    }


    //Comando2
    pid_t pid2= fork();
    
    if(pid2 == -1){
        perror("fork");
        exit(1);
    }
    else if(pid2 == 0){//Hijo
        close(c1_c2[1]);
        printf("Hijo 2 pid : %d\n", getpid());
        dup2(c1_c2[0],0);

        execvp(comando2,argv+2);

    }
    else{//Padre
        wait(NULL);
    }




    return 0;
}